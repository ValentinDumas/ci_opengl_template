# ------------------------------------------------------------------------------
# Tests: integration
# ------------------------------------------------------------------------------
set(PROJECT_INTEGRATION_TEST_FILES test_integration_main.cpp test_robot.cpp)

add_executable(integration_tests ${PROJECT_INTEGRATION_TEST_FILES})
target_link_libraries(integration_tests PRIVATE ${EXTERNAL_MODULES} ${PROJECT_SOURCE_MODULES}) #Note: see if glfw has to be included...
target_compile_definitions(integration_tests PRIVATE main_integration_tests=main)

# This is so you can do 'make test' to see all your tests run, instead of
# manually running the executable runUnitTests to see those specific tests.
add_test(NAME integration_tests COMMAND integration_tests)

# Expose library to parent folder --> to execute ALL TESTS
add_library(integration_tests_lib STATIC ${PROJECT_INTEGRATION_TEST_FILES})