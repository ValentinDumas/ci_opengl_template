# ------------------------------------------------------------------------------
# File: CMakeLists.txt
# Created by Spark on 28/04/2019.
# ------------------------------------------------------------------------------

project(opengl3_imgui_example)

# ------------------------------------------------------------------------------
# Target details
# ------------------------------------------------------------------------------
set(${PROJECT_NAME}_SOURCE_FILES opengl3_imgui_example.cpp)
set(${PROJECT_NAME}_INCLUDE_DIRS "") # by including this, we have access to all other submodules folders even from "examples" and "tests" folders
set(${PROJECT_NAME}_LIBRARIES imgui glfw glad)
set(${PROJECT_NAME}_COVERAGE OFF)
set(${PROJECT_NAME}_WARNINGS OFF)

# ------------------------------------------------------------------------------
# Target executable
# ------------------------------------------------------------------------------
add_custom_executable(${PROJECT_NAME} "${${PROJECT_NAME}_SOURCE_FILES}" PUBLIC "${${PROJECT_NAME}_INCLUDE_DIRS}" "${${PROJECT_NAME}_LIBRARIES}" ${PROJECT_NAME}_COVERAGE ${PROJECT_NAME}_WARNINGS)