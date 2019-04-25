project(integration_tests)

# ------------------------------------------------------------------------------
# Integration Tests Files
# ------------------------------------------------------------------------------
set(PROJECT_INTEGRATION_TEST_FILES test_robot.cpp) # without main executable

set(INTEGRATION_TESTING_DEPENDENCIES glm) # Note: error proof. CMake throws an error if

# ------------------------------------------------------------------------------
# Integration Tests Executable
# ------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} test_integration_main.cpp ${PROJECT_INTEGRATION_TEST_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${TESTING_DEPENDENCIES} ${INTEGRATION_TESTING_DEPENDENCIES} ${PROJECT_SOURCE_MODULES}) #Note: see if glfw has to be included...
target_compile_definitions(${PROJECT_NAME} PRIVATE test_integration_main=main)

if(MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE MSVC_PLATFORM)
endif()

MoveNeededResourcesToTarget(${PROJECT_NAME})

# ------------------------------------------------------------------------------
# Integration Tests: console & coverage
# ------------------------------------------------------------------------------
macro(CreateIntegrationTest test_name relative_test_dir)
    CreateTest(integration ${test_name} ${relative_test_dir} "${INTEGRATION_TESTING_DEPENDENCIES}")
endmacro()

#add_test(${PROJECT_NAME} ${PROJECT_NAME})
CreateIntegrationTest(test_robot ${CMAKE_CURRENT_SOURCE_DIR})