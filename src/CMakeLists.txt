project(ci_opengl_template)

# ------------------------------------------------------------------------------
# PROJECT MODULES MANAGEMENT (FUNCTIONS)
# ------------------------------------------------------------------------------
create_property(P_PROJECT_SOURCE_MODULES "")

function(add_custom_library target_type target_name sources includes_scope includes_string libraries_string GENERATE_COVERAGE GENERATE_WARNINGS)
    # Limits: can only define one scope for the "target_include_directories", as this CMake function requires the scope as a parameter
    # Create a library with a name, a type (shared, static or interface))
    add_library(${target_name} ${target_type} ${sources})

    # Bind one or more directory to the target
    target_include_directories(${target_name} ${includes_scope} ${includes_string}) # Note: see if it includes .hpp && .cpp OR only .cpp files

    if(GENERATE_COVERAGE) # coverage enabled
        list(APPEND libraries_string coverage_config)
    endif()
    if(GENERATE_WARNINGS) # warnings enabled
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
    # ...
endfunction()

# ------------------------------------------------------------------------------
# MAIN EXECUTABLE
# ------------------------------------------------------------------------------
# TODO: create a variable CI_OPENGL_TEMPLATE_PROJECT_SOURCE_MODULES
set(CI_OPENGL_TEMPLATE_LIBRARIES imgui glfw glad glm stb Box2D cppfs mathematics)

add_executable(ci_opengl_template imgui_main.cpp)

target_link_libraries(ci_opengl_template ${CI_OPENGL_TEMPLATE_LIBRARIES})

if (MSVC)
    target_compile_definitions(ci_opengl_template PRIVATE MSVC_PLATFORM)
endif()

MoveNeededResourcesToTarget(ci_opengl_template)

# ------------------------------------------------------------------------------
# PROJECT MODULES
# ------------------------------------------------------------------------------
add_subdirectory(mathematics)