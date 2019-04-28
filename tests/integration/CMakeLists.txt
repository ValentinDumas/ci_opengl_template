# ------------------------------------------------------------------------------
# File: CMakeLists.txt
# Created by Spark on 28/04/2019.
# ------------------------------------------------------------------------------

project(integration_tests)

# ------------------------------------------------------------------------------
# Target details
# ------------------------------------------------------------------------------
GetRecursiveItemsFromPath(${PROJECT_NAME}_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")
set(${PROJECT_NAME}_INCLUDE_DIRS "")
set(${PROJECT_NAME}_LIBRARIES ${TESTS_LIBRARIES} glm ${PROJECT_SOURCE_MODULES})
set(${PROJECT_NAME}_COVERAGE ON)
set(${PROJECT_NAME}_WARNINGS OFF)

# ------------------------------------------------------------------------------
# Target executable
# ------------------------------------------------------------------------------
add_custom_executable(${PROJECT_NAME} "${${PROJECT_NAME}_SOURCE_FILES}" PUBLIC "${${PROJECT_NAME}_INCLUDE_DIRS}" "${${PROJECT_NAME}_LIBRARIES}" ${PROJECT_NAME}_COVERAGE ${PROJECT_NAME}_WARNINGS)

# ------------------------------------------------------------------------------
# Create integration tests
# ------------------------------------------------------------------------------
macro(CreateIntegrationTest test_name relative_test_dir)
    CreateTest(integration ${test_name} ${relative_test_dir} "${${PROJECT_NAME}_LIBRARIES}")
endmacro()

# Note: Write the name and the relative directory for a test you want to create.
CreateIntegrationTest(test_robot ${CMAKE_CURRENT_SOURCE_DIR})

# ------------------------------------------------------------------------------
# Integration tests subdirectories
# ------------------------------------------------------------------------------
# Note: All subdirectories containing can be written there.