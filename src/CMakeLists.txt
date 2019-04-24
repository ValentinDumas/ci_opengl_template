# ------------------------------------------------------------------------------
# FUNCTIONS
# ------------------------------------------------------------------------------
#Note: Adds a target's name to the main project.
#Note: If you want to set an other property than the P_PROJECT_SOURCE_MODULES, refers to the "add_data_to_property" function.
function(add_target_to_main_project module_name)
    get_property_by_name(property_output P_PROJECT_SOURCE_MODULES)
    if(property_output STREQUAL "") # empty
        set_property(GLOBAL PROPERTY P_PROJECT_SOURCE_MODULES "${module_name}")
    else() # at least one module registered
        set_property(GLOBAL PROPERTY P_PROJECT_SOURCE_MODULES "${property_output} ${module_name}")
    endif()
    message("Added target ${module_name} as a module")
endfunction()

create_property(P_PROJECT_SOURCE_MODULES "")

# ------------------------------------------------------------------------------
# MAIN EXECUTABLE
# ------------------------------------------------------------------------------
set(ci_opengl_template_libraries imgui glfw ${GLFW_LIBRARIES} glad ${GLAD_LIBRARIES} glm stb Box2D mathematics cppfs)

add_executable(ci_opengl_template imgui_main.cpp)
target_link_libraries(ci_opengl_template ${ci_opengl_template_libraries})

if (MSVC)
    target_compile_definitions(ci_opengl_template PRIVATE main=main MSVC_PLATFORM)
endif()

MoveNeededResourcesToTarget(ci_opengl_template)

# ------------------------------------------------------------------------------
# PROJECT MODULES
# ------------------------------------------------------------------------------
add_subdirectory(mathematics)

# ------------------------------------------------------------------------------
# GET REGISTERED PROJECT MODULES
# ------------------------------------------------------------------------------
get_property_by_name(PROJECT_SOURCE_MODULES P_PROJECT_SOURCE_MODULES)
message("${PROJECT_SOURCE_MODULES}")