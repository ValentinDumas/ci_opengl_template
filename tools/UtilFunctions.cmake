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
    elseif(BUILD_EXECUTABLE_IN_PROJECT_TREE AND (target_name MATCHES "test")) # STANDALONE && EXE BUILDING in project tree
        message("Manually copy GOOGLE TEST/MOCK shared libraries (.dll) to project binary directory to build executable directly into the project folder instead of Cmake default binary folder")
        MoveLibToTarget(gtest ${target_name})
        MoveLibToTarget(gmock ${target_name})
        MoveLibToTarget(gtest_main ${target_name})
        MoveLibToTarget(gmock_main ${target_name})
    endif()
endfunction()

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

#TODO: function to easily set all kinds of GLOBAL properties
function(add_data_to_property property_name module_name)
    get_property_by_name(property_output ${property_name})
    if(property_output STREQUAL "") # empty
        set_property(GLOBAL PROPERTY ${property_name} "${module_name}")
    else() # at least one module registered
        set_property(GLOBAL PROPERTY ${property_name} ${property_output} ${module_name})
    endif()
    #message("(add_data_to_property) Added target ${module_name} as a module")
endfunction()

function(MoveFolderToTarget target_name source_path path_relative_to_target)
    add_custom_command(TARGET ${target_name}
            PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${source_path}
            $<TARGET_FILE_DIR:${target_name}>\\${path_relative_to_target})
endfunction()

function(AddLibraryToProject library_name)
    GetLibraryType(${library_name})
    #message("(AddLibraryToTarget) Library ${library_name} is a ${library_type}")
    if(library_type STREQUAL SHARED_LIBRARY)
        add_data_to_property(P_SHARED_LIBRARIES ${library_name})
    elseif(library_type STREQUAL STATIC_LIBRARY)
        add_data_to_property(P_STATIC_LIBRARIES ${library_name})
    else()
        add_data_to_property(P_INTERFACE_LIBRARIES ${library_name})
    endif()
endfunction()

function(GetRecursiveItemsFromPath items_returned root_path pattern)
    # Look for items matching a given pattern
    file(GLOB_RECURSE items_found ${pattern})

    # Extract relative paths from root (absolute) paths
    foreach (item_path ${items_found})
        string(REPLACE "${root_path}/" "" item_relative_path ${item_path})
        list(APPEND items ${item_relative_path})
    endforeach ()

    # Return variable, containing all items found
    set(${items_returned} ${items} PARENT_SCOPE)
endfunction()

# Get a list of all subdirectories, starting from a given path
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