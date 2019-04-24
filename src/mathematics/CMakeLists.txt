project_as_directory_name()

set(${PROJECT_NAME}_SOURCE_FILES complex.cpp)
set(${PROJECT_NAME}_LIBRARIES "")

# Limits: can only define one scope for the "target_include_directories", as this CMake function requires the scope as a parameter
function(ADD_CUSTOM_LIBRARY target_type target_name sources includes_scope includes_string libraries_string)
    set(${target_name}_SOURCE_FILES complex.cpp)

    add_library(${target_name} ${target_type} ${${target_name}_SOURCE_FILES})

    target_include_directories(${target_name} ${includes_scope} ${includes_string}) # Note: see if it includes .hpp && .cpp OR only .cpp files

    list(APPEND libraries_string coverage_config warnings_config)
    message("CUUUUUUUUUUUUUUUUUUUU ${libraries_string}")
    target_link_libraries(${target_name} PRIVATE ${libraries_string}) # Include code-coverage & warnings settings

    # Define this target as a project source's module
    add_target_to_main_project(${target_name})

    # Register the target name as a STATIC or a SHARED library, depending on the ${target_type} set
    AddLibraryToProject(${target_name})
endfunction()

ADD_CUSTOM_LIBRARY(STATIC ${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE_FILES} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" "${${PROJECT_NAME}_LIBRARIES}")