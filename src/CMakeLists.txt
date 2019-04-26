project(ci_opengl_template)

# ------------------------------------------------------------------------------
# MAIN EXECUTABLE
# ------------------------------------------------------------------------------
# TODO: create a variable CI_OPENGL_TEMPLATE_PROJECT_SOURCE_MODULES
set(${PROJECT_NAME}_SOURCE_FILES imgui_main.cpp)
set(${PROJECT_NAME}_INCLUDE_DIRS "") # by including this, we have access to all other submodules folders even from "examples" and "tests" folders
set(${PROJECT_NAME}_LIBRARIES imgui glfw glad glm stb Box2D cppfs mathematics assimp)
set(${PROJECT_NAME}_COVERAGE ON)
set(${PROJECT_NAME}_WARNINGS ON)

add_custom_executable(${PROJECT_NAME} "${${PROJECT_NAME}_SOURCE_FILES}" PUBLIC "${${PROJECT_NAME}_INCLUDE_DIRS}" "${${PROJECT_NAME}_LIBRARIES}" ${PROJECT_NAME}_COVERAGE ${PROJECT_NAME}_WARNINGS)

# ------------------------------------------------------------------------------
# PROJECT MODULES
# ------------------------------------------------------------------------------
add_subdirectory(mathematics)