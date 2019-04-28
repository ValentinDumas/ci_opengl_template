# ------------------------------------------------------------------------------
# File: CMakeLists.txt
# Created by Spark on 28/04/2019.
# ------------------------------------------------------------------------------

# TODO (note): keep an eye on PROJECT_SOURCE_MODULES: as the tests automatically link against all project modules, it may trigger a "Coverage report error" on CodeCov if a module is linked to glfw or glad.
include_directories(${gtest_SOURCE_DIR}/include)
include_directories(${gmock_SOURCE_DIR}/include)

# ------------------------------------------------------------------------------
# Test Libraries
# ------------------------------------------------------------------------------
set(TESTS_LIBRARIES gtest gtest_main gmock gmock_main)

# ------------------------------------------------------------------------------
# Project Modules (all modules in a list)
# ------------------------------------------------------------------------------
get_property_by_name(PROJECT_SOURCE_MODULES P_PROJECT_SOURCE_MODULES)

# ------------------------------------------------------------------------------
# Create CTest tests one by one --> detailed test execution (usefull for bot VS and Online testing)
# ------------------------------------------------------------------------------
macro(CreateTest TYPE NAME PATH_TO_TEST ADDITIONAL_TESTS_DEPENDENCIES)
	set(TEST_NAME ${TYPE}_${NAME})
	add_executable(${TEST_NAME} ${PATH_TO_TEST}/${NAME}.cpp)
	target_link_libraries(${TEST_NAME} PRIVATE ${TESTS_LIBRARIES} ${ADDITIONAL_TESTS_DEPENDENCIES} coverage_config) #Note: no detailed warnings (from gtest macro)
    add_test(NAME ${TEST_NAME} COMMAND $<TARGET_FILE:${TEST_NAME}>)
endmacro()

# ------------------------------------------------------------------------------
# Main Tests
# ------------------------------------------------------------------------------
add_subdirectory(integration)
add_subdirectory(unit)