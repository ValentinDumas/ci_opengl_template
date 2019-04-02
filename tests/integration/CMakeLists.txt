project(integration_tests)

# ------------------------------------------------------------------------------
# Integration Tests Files
# ------------------------------------------------------------------------------
set(PROJECT_INTEGRATION_TEST_FILES test_robot.cpp) # without main executable

# ------------------------------------------------------------------------------
# Integration Tests Executable
# ------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} test_integration_main.cpp ${PROJECT_INTEGRATION_TEST_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${EXTERNAL_MODULES} ${PROJECT_SOURCE_MODULES}) #Note: see if glfw has to be included...
target_compile_definitions(${PROJECT_NAME} PRIVATE test_integration_main=main)

MoveLibToTarget(glm_static ${PROJECT_NAME})

#
#install(TARGETS ${PROJECT_NAME} ${CMAKE_BINARY_DIR}/bin) # for 'make install' command on macOS/Unix

# ------------------------------------------------------------------------------
# Integration Tests: console & coverage
# ------------------------------------------------------------------------------
add_test(${PROJECT_NAME} ${PROJECT_NAME})

# ------------------------------------------------------------------------------
# Unit Tests: Visual Studio
# ------------------------------------------------------------------------------
# Add tests individually if MSVC
#if(MSVC)
#    message("Import tests for MSVC environment")
#    # Note: possibility to perform a 'add_subdirectory' here and then 'CreateTest()' in that directory
#    CreateTest(test_complex) # not working with ctest on appveyor ?
#endif()