project(cppfs_example)

# ------------------------------------------------------------------------------
# TARGET DETAILS
# ------------------------------------------------------------------------------
set(${PROJECT_NAME}_SOURCE_FILES cppfs_example.cpp)
set(${PROJECT_NAME}_INCLUDE_DIRS "") # by including this, we have access to all other submodules folders even from "examples" and "tests" folders
set(${PROJECT_NAME}_LIBRARIES cppfs)
set(${PROJECT_NAME}_COVERAGE OFF)
set(${PROJECT_NAME}_WARNINGS OFF)

# ------------------------------------------------------------------------------
# TARGET EXECUTABLE
# ------------------------------------------------------------------------------
add_custom_executable(${PROJECT_NAME} "${${PROJECT_NAME}_SOURCE_FILES}" PUBLIC "${${PROJECT_NAME}_INCLUDE_DIRS}" "${${PROJECT_NAME}_LIBRARIES}" ${PROJECT_NAME}_COVERAGE ${PROJECT_NAME}_WARNINGS)
