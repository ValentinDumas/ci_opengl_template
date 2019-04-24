# TODO (note): keep an eye on PROJECT_SOURCE_MODULES: as the tests automatically link against all project modules, it may trigger a "Coverage report error" on CodeCov if a module is linked to glfw or glad.

# ------------------------------------------------------------------------------
# Includes (googletest and googlemock)
# ------------------------------------------------------------------------------
# TODO: Can bind the directories to the gtest/gmock targets respectively
include_directories(${gtest_SOURCE_DIR}/include)
include_directories(${gmock_SOURCE_DIR}/include)

# ------------------------------------------------------------------------------
# Dependency Libraries: from "deps" and / or "externals"
# ------------------------------------------------------------------------------
set(TESTING_DEPENDENCIES gtest gtest_main gmock gmock_main)

# ------------------------------------------------------------------------------
# Create CTest tests one by one --> detailed test execution (usefull for bot VS and Online testing)
# ------------------------------------------------------------------------------
function(CreateTest TYPE NAME PATH_TO_TEST ADDITIONAL_TESTING_DEPENDENCIES)
	set(TEST_NAME ${TYPE}_${NAME})
	add_executable(${TEST_NAME} ${PATH_TO_TEST}/${NAME}.cpp)
	target_link_libraries(${TEST_NAME} PRIVATE ${TESTING_DEPENDENCIES} ${ADDITIONAL_TESTING_DEPENDENCIES} "${PROJECT_SOURCE_MODULES}" coverage_config) #Note: see if glfw has to be included...
    add_test(NAME ${TEST_NAME} COMMAND $<TARGET_FILE:${TEST_NAME}> )
endfunction()

# ------------------------------------------------------------------------------
# Main Tests
# ------------------------------------------------------------------------------
add_subdirectory(integration)
add_subdirectory(unit)
