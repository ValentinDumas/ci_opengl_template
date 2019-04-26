project(unit_tests)

# ------------------------------------------------------------------------------
# UNIT TESTS: FILES
# ------------------------------------------------------------------------------
GetRecursiveItemsFromPath(${PROJECT_NAME}_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")
set(${PROJECT_NAME}_INCLUDE_DIRS "")
set(${PROJECT_NAME}_LIBRARIES ${TESTS_LIBRARIES} glm ${PROJECT_SOURCE_MODULES})
set(${PROJECT_NAME}_COVERAGE ON)
set(${PROJECT_NAME}_WARNINGS OFF)

# ------------------------------------------------------------------------------
# UNIT TESTS: EXECUTABLE
# ------------------------------------------------------------------------------
add_custom_executable(${PROJECT_NAME} "${${PROJECT_NAME}_SOURCE_FILES}" PUBLIC "${${PROJECT_NAME}_INCLUDE_DIRS}" "${${PROJECT_NAME}_LIBRARIES}" ${PROJECT_NAME}_COVERAGE ${PROJECT_NAME}_WARNINGS)

# ------------------------------------------------------------------------------
# UNIT TESTS: FUNCTIONS
# ------------------------------------------------------------------------------
macro(CreateUnitTest test_name relative_test_dir)
    CreateTest(unit ${test_name} "${relative_test_dir}" "${UNIT_TESTS_LIBRARIES}")
endmacro()

# ------------------------------------------------------------------------------
# UNIT TESTS: TESTS
# ------------------------------------------------------------------------------
CreateUnitTest(test_robot ${CMAKE_CURRENT_SOURCE_DIR})

# ------------------------------------------------------------------------------
# UNIT TESTS: SUB-TESTS
# ------------------------------------------------------------------------------
add_subdirectory(mathematics)