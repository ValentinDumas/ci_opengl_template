# ------------------------------------------------------------------------------
# CMAKE VERSION
# ------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.6)

# ------------------------------------------------------------------------------
# PROJECT INFORMATION
# ------------------------------------------------------------------------------
project(ci_opengl_template C CXX)

# ------------------------------------------------------------------------------
# CMAKE BUILD TYPEs: DEBUG or RELEASE
# ------------------------------------------------------------------------------
#set(CMAKE_BUILD_TYPE Debug)
#message(CMAKE Build Type => ${CMAKE_BUILD_TYPE})

# ------------------------------------------------------------------------------
# CMAKE OPTIONS
# ------------------------------------------------------------------------------
#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

# Turn off shared libs to manage static/shared libraries
set(BUILD_SHARED_LIBS OFF)
if(MSVC)
    set(BUILD_SHARED_LIBS OFF) # force STATIC builds on MSVC
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STDC_CONSTANT_MACROS")
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # enable it before using "clang tidy"

# Note: Can be OFF when testing (CI). Turn ON only to build an executable directly in project instead of CMake binary folder
set(BUILD_EXECUTABLE_IN_PROJECT_TREE ON)

# ------------------------------------------------------------------------------
# PROJECT MODULES MANAGEMENT (FUNCTIONS)
# ------------------------------------------------------------------------------
function(add_custom_library target_type target_name sources includes_scope includes_string libraries_string GENERATE_COVERAGE GENERATE_WARNINGS)
    # Limits: can only define one scope for the "target_include_directories", as this CMake function requires the scope as a parameter
    # Create a library with a name, a type (shared, static or interface))
    add_library(${target_name} ${target_type} ${sources})

    # Bind one or more directory to the target
    target_include_directories(${target_name} ${includes_scope} ${includes_string}) # Note: see if it includes .hpp && .cpp OR only .cpp files

    if(${${GENERATE_COVERAGE}}) # coverage enabled
        list(APPEND libraries_string coverage_config)
    endif()
    if(${${GENERATE_WARNINGS}}) # warnings enabled
        list(APPEND libraries_string warnings_config)
    endif()

    # "PRIVATE" libraries, exclusively linked to the target
    target_link_libraries(${target_name} PRIVATE ${libraries_string}) # Include code-coverage & warnings settings

    # Define this target as a project source's module
    add_data_to_property(P_PROJECT_SOURCE_MODULES ${target_name})

    # Register the target name as a STATIC or a SHARED library, depending on the ${target_type} set
    AddLibraryToProject(${target_name})
endfunction()

function(add_custom_executable target_name sources includes_scope includes_string libraries_string GENERATE_COVERAGE GENERATE_WARNINGS)
    add_executable(${target_name} ${sources})

    #TODO: set this condition to make the function GENERIC for all types of executables
    if(NOT(includes_scope STREQUAL "")) # include public headers
        target_include_directories(${target_name} ${includes_scope} ${includes})
    endif()

    if(${${GENERATE_COVERAGE}}) # coverage enabled
        list(APPEND libraries_string coverage_config)
    endif()
    if(${${GENERATE_WARNINGS}}) # warnings enabled
        list(APPEND libraries_string warnings_config)
    endif()

    message("Libraries to link to target ${target_name}: ${libraries_string}")

    target_link_libraries(${target_name} PRIVATE ${libraries_string})

    if (MSVC)
        target_compile_definitions(${target_name} PRIVATE MSVC_PLATFORM)
    endif()

    MoveNeededResourcesToTarget(${target_name})
endfunction()

macro(project_as_directory_name)
    get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    string(REPLACE " " "_" ProjectId ${ProjectId})
    project(${ProjectId})
endmacro()

macro(GetLibraryType library_name)
    set(library_type "" PARENT_SCOPE)
    get_target_property(library_type ${library_name} TYPE)
    if(library_type STREQUAL SHARED_LIBRARY)
        set(library_type SHARED PARENT_SCOPE)
    else()
        set(library_type STATIC PARENT_SCOPE)
    endif()
endmacro()

function(MoveLibToTarget lib_name target_name)
    if((NOT (target_name STREQUAL "gtest_main")) )
        add_custom_command(TARGET ${target_name} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<TARGET_FILE:${lib_name}>"
                "$<TARGET_FILE_DIR:${target_name}>"
                VERBATIM)
        message("Moving library [${lib_name}] at target [${target_name}]")
    endif()
endfunction()

function(MoveMultipleLibsForTarget libraries target_name)
    if(libraries STREQUAL "") # no input libraries (static or shared)
        message("->[Warning] In 'MoveMultipleLibsForTarget' function: no input libraries.")
    else()
        foreach(library ${libraries})
            MoveLibToTarget(${library} ${target_name})
        endforeach()
    endif()
endfunction()

macro(create_property property_name value)
    set_property(GLOBAL PROPERTY ${property_name} ${value})
endmacro()

function(get_property_by_name output_name property_to_extract)
    get_property(property_values GLOBAL PROPERTY ${property_to_extract})
    set(${output_name} ${property_values} CACHE STRING "An extracted property's name" FORCE)
endfunction()

create_property(P_PROJECT_SOURCE_MODULES "")

#TODO: function to easily set all kinds of GLOBAL properties
function(add_data_to_property property_name module_name)
    get_property_by_name(property_output ${property_name})
    if(property_output STREQUAL "") # empty
        set_property(GLOBAL PROPERTY ${property_name} "${module_name}")
    else() # at least one module registered
        set_property(GLOBAL PROPERTY ${property_name} ${property_output} ${module_name})
    endif()
    message("(add_data_to_property) Added target ${module_name} as a module")
endfunction()

function(MoveNeededResourcesToTarget target_name) # TODO: add "required_libraries" parameter to avoid copying all dlls for each target even when they don't need it.
    get_property_by_name(SHARED_LIBRARIES P_SHARED_LIBRARIES)

    if(ONLINE_MODE) # online --> move assets to CMake's default binary folder
        if(MSVC)
            message("MSVC building...")
            MoveAssetsToTarget("${CMAKE_SOURCE_DIR}\\assets" ${target_name})
        else()
            MoveAssetsToTarget("${CMAKE_SOURCE_DIR}\\assets" ${target_name})
        endif()

        MoveMultipleLibsForTarget("${SHARED_LIBRARIES}" ${target_name})
    elseif(BUILD_EXECUTABLE_IN_PROJECT_TREE) # STANDALONE && EXE BUILDING in project tree
        message("Manually copy GOOGLE TEST/MOCK shared libraries (.dll) to project binary directory to build executable directly into the project folder instead of Cmake default binary folder")
        MoveLibToTarget(gtest ${target_name})
        MoveLibToTarget(gmock ${target_name})
        MoveLibToTarget(gtest_main ${target_name})
        MoveLibToTarget(gmock_main ${target_name})
    endif()
endfunction()

# ------------------------------------------------------------------------------
# TESTING MODE OPTIONS
# Note: Default testing mode as STANDALONE (offline)
# ------------------------------------------------------------------------------
#Note: If ONLINE OR STANDALONE_WITH_NOEXECUTABLE Then
#set(ONLINE_TESTING ON)
set(ONLINE_MODE ${ONLINE_TESTING})
if(ONLINE_MODE)
    message("Tests are configured in ONLINE mode")
else()
    message("Tests are configured in STANDALONE mode")
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static") # include gcc libs
    if(BUILD_EXECUTABLE_IN_PROJECT_TREE)
        # TODO: only apply to concerned target, as main target (ci_opengl_template) for instance
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}\\bin") # sure ?
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}\\bin") # TODO: change to lib
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}\\bin\\static") # TODO: change to lib/static
    else()
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}\\bin") # sure ?
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}\\bin") # TODO: change to lib
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}\\bin\\static") # TODO: change to lib/static
    endif()
endif()

# GET A LIST OF ALL SUBIDRECTORIES FROM A CURRENT PATH
MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

# ------------------------------------------------------------------------------
# ASSETS
# ------------------------------------------------------------------------------
add_subdirectory(assets)

# ------------------------------------------------------------------------------
# EXTERNALS (DEPENDENCIES)
# ------------------------------------------------------------------------------
#TODO: change to external && remove externals
add_subdirectory(externals)

# ------------------------------------------------------------------------------
# SOURCES
# ------------------------------------------------------------------------------
add_subdirectory(src)

# ------------------------------------------------------------------------------
# CTEST -> TESTING
# ------------------------------------------------------------------------------
option (BUILD_TESTING "Build the testing tree." ON)
# Only build tests if we are the top-level project
# Allows this to be used by super projects with `add_subdirectory`
if (BUILD_TESTING AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
    include(CTest)
    add_subdirectory(tests)
endif()

# ------------------------------------------------------------------------------
# EXAMPLES
# ------------------------------------------------------------------------------
set(BUILD_EXAMPLES ON)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# ------------------------------------------------------------------------------
# DEBUGGING INFO: LIBRARY LISTS
# ------------------------------------------------------------------------------
get_property_by_name(SHARED_LIBRARIES P_SHARED_LIBRARIES)
get_property_by_name(STATIC_LIBRARIES P_STATIC_LIBRARIES)
get_property_by_name(INTERFACE_LIBRARIES P_INTERFACE_LIBRARIES)
message("SHARED LIBRARIES for the whole solution: ${SHARED_LIBRARIES}")
message("STATIC LIBRARIES for the whole solution: ${STATIC_LIBRARIES}")
message("INTERFACE LIBRARIES for the whole solution: ${INTERFACE_LIBRARIES}")

