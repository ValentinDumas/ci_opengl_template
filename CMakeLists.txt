# ------------------------------------------------------------------------------
# CMAKE VERSION
# ------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.6)

# ------------------------------------------------------------------------------
# PROJECT INFORMATION
# ------------------------------------------------------------------------------
project(ci_opengl_template C CXX)

# ------------------------------------------------------------------------------
# CMAKE OPTIONS
# ------------------------------------------------------------------------------
#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

set(BUILD_SHARED_LIBS OFF)
if(MSVC)
    set(BUILD_SHARED_LIBS OFF) # force STATIC builds on MSVC
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STDC_CONSTANT_MACROS")
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # enable it before using "clang tidy"

# Note: Must be OFF when testing (CI)
set(BUILD_EXECUTABLE_IN_PROJECT_TREE OFF)

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
    add_custom_command(TARGET ${target_name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:${lib_name}>"
            "$<TARGET_FILE_DIR:${target_name}>"
            VERBATIM)
    message("Moving library [${lib_name}] at target [${target_name}]")
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

create_property(CUSTOM_SHARED_LIBRARIES "")

#TODO: function to easily set all kinds of GLOBAL properties
function(add_data_to_property property_name module_name)
    get_property_by_name(property_output ${property_name})
    if(property_output STREQUAL "") # empty
        set_property(GLOBAL PROPERTY ${property_name} "${module_name}")
    else() # at least one module registered
        set_property(GLOBAL PROPERTY ${property_name} "${property_output} ${module_name}")
    endif()
    message("(add_data_to_property) Added target ${module_name} as a module")
endfunction()

function(MoveNeededResourcesToTarget target_name ) # TODO: add "required_libraries" parameter to avoid copying all dlls for each target even when they don't need it.
    get_property_by_name(SHARED_LIBRARIES P_SHARED_LIBRARIES)

    if(ONLINE_MODE) # online --> move assets to CMake's default binary folder
        if(MSVC)
            message("MSVC building...")
            MoveAssetsToTarget("${CMAKE_SOURCE_DIR}\\assets" ${target_name})
            MoveMultipleLibsForTarget("${SHARED_LIBRARIES}" ${target_name})
        else()
            MoveAssetsToTarget("${CMAKE_SOURCE_DIR}\\assets" ${target_name})
            MoveMultipleLibsForTarget("${SHARED_LIBRARIES}" ${target_name})
        endif()
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

        # TODO: create CopyFile function (source_path, destination_path) !
        # TODO: create CopyFileToTarget function ?
#        message("Manually copy GOOGLE TEST/MOCK shared libraries (.dll) to project binary directory to build executable directly into the project folder instead of Cmake default binary folder")
#        configure_file(${CMAKE_BINARY_DIR}/bin/libgtestd.dll ${CMAKE_SOURCE_DIR}/bin/libgtestd.dll COPYONLY)
#        configure_file(${CMAKE_BINARY_DIR}/bin/libgtest_maind.dll ${CMAKE_SOURCE_DIR}/bin/libgtest_maind.dll COPYONLY)
#        configure_file(${CMAKE_BINARY_DIR}/bin/libgmockd.dll ${CMAKE_SOURCE_DIR}/bin/libgmockd.dll COPYONLY)
#        configure_file(${CMAKE_BINARY_DIR}/bin/libgmock_maind.dll ${CMAKE_SOURCE_DIR}/bin/libgmock_maind.dll COPYONLY)
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
# EXTERNAL DEPENDENCIES
# ------------------------------------------------------------------------------
#TODO: change to external && remove externals
add_subdirectory(deps)

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
# DEBUGGING INFORMATION
# ------------------------------------------------------------------------------
get_property_by_name(SHARED_LIBRARIES P_SHARED_LIBRARIES)
get_property_by_name(STATIC_LIBRARIES P_STATIC_LIBRARIES)
get_property_by_name(INTERFACE_LIBRARIES P_INTERFACE_LIBRARIES)
message("SHARED LIBRARIES for the whole solution: ${SHARED_LIBRARIES}")
message("STATIC LIBRARIES for the whole solution: ${STATIC_LIBRARIES}")
message("INTERFACE LIBRARIES for the whole solution: ${INTERFACE_LIBRARIES}")
