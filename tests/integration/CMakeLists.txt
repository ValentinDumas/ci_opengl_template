project(integration_tests)

# ------------------------------------------------------------------------------
# INTEGRATION TESTS: FILES
# ------------------------------------------------------------------------------
GetRecursiveItemsFromPath(${PROJECT_NAME}_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")
set(${PROJECT_NAME}_INCLUDE_DIRS "")
set(${PROJECT_NAME}_LIBRARIES ${TESTS_LIBRARIES} glm ${PROJECT_SOURCE_MODULES})
set(${PROJECT_NAME}_COVERAGE ON)
set(${PROJECT_NAME}_WARNINGS OFF)

# ------------------------------------------------------------------------------
# INTEGRATION TESTS: EXECUTABLE
# ------------------------------------------------------------------------------
add_custom_executable(${PROJECT_NAME} "${${PROJECT_NAME}_SOURCE_FILES}" PUBLIC "${${PROJECT_NAME}_INCLUDE_DIRS}" "${${PROJECT_NAME}_LIBRARIES}" ${PROJECT_NAME}_COVERAGE ${PROJECT_NAME}_WARNINGS)

# ------------------------------------------------------------------------------
# INTEGRATION TESTS: FUNCTIONS
# ------------------------------------------------------------------------------
macro(CreateIntegrationTest test_name relative_test_dir)
    CreateTest(integration ${test_name} ${relative_test_dir} "${INTEGRATION_TESTING_LIBRARIES}")
endmacro()

# ------------------------------------------------------------------------------
# INTEGRATION TESTS: TESTS
# ------------------------------------------------------------------------------
CreateIntegrationTest(test_robot ${CMAKE_CURRENT_SOURCE_DIR})

# ------------------------------------------------------------------------------
# INTEGRATION TESTS: SUB-TESTS
# ------------------------------------------------------------------------------