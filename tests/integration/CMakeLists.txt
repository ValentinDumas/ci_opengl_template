# ------------------------------------------------------------------------------
# Tests: integration
# ------------------------------------------------------------------------------
set(PROJECT_INTEGRATION_TEST_FILES test_robot.cpp) # without main executable

add_executable(integration_tests test_integration_main.cpp ${PROJECT_INTEGRATION_TEST_FILES})
target_link_libraries(integration_tests PRIVATE ${EXTERNAL_MODULES} ${PROJECT_SOURCE_MODULES}) #Note: see if glfw has to be included...
target_compile_definitions(integration_tests PRIVATE test_integration_main=main)

if(STANDALONE_TESTING)
    message("Unit tests started in STANDALONE mode")
else()
    message("Unit tests started in ONLINE mode")
endif()

add_test(tests integration_tests)