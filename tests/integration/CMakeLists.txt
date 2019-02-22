# ------------------------------------------------------------------------------
# Tests: integration
# ------------------------------------------------------------------------------
set(PROJECT_INTEGRATION_TEST_FILES complex_main.cpp ../unit/test_hello.cpp)
add_executable(integration_tests ${PROJECT_INTEGRATION_TEST_FILES})
target_link_libraries(integration_tests PRIVATE gtest gtest_main gmock gmock_main project_src_lib) #Note: see if glfw has to be included...
target_compile_definitions(integration_tests PRIVATE main_tests=main)

# This is so you can do 'make test' to see all your tests run, instead of
# manually running the executable runUnitTests to see those specific tests.
add_test(NAME integration_tests COMMAND integration_tests)