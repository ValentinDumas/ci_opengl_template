# ------------------------------------------------------------------------------
# Integration Tests Files
# ------------------------------------------------------------------------------
set(PROJECT_INTEGRATION_TEST_FILES test_robot.cpp) # without main executable

# ------------------------------------------------------------------------------
# Integration Tests Executable
# ------------------------------------------------------------------------------
add_executable(integration_tests test_integration_main.cpp ${PROJECT_INTEGRATION_TEST_FILES})
target_link_libraries(integration_tests PRIVATE ${EXTERNAL_MODULES} ${PROJECT_SOURCE_MODULES}) #Note: see if glfw has to be included...
target_compile_definitions(integration_tests PRIVATE test_integration_main=main)

# ------------------------------------------------------------------------------
# Integration Tests: console & coverage
# ------------------------------------------------------------------------------
add_test(integration_tests integration_tests)

# ------------------------------------------------------------------------------
# Unit Tests: Visual Studio
# ------------------------------------------------------------------------------
# Add tests individually if MSVC
#if(MSVC)
#    message("Import tests for MSVC environment")
#    # Note: possibility to perform a 'add_subdirectory' here and then 'CreateTest()' in that directory
#    CreateTest(test_complex) # not working with ctest on appveyor ?
#endif()