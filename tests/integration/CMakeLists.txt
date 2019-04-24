project(integration_tests)

# ------------------------------------------------------------------------------
# Integration Tests Files
# ------------------------------------------------------------------------------
set(PROJECT_INTEGRATION_TEST_FILES test_robot.cpp) # without main executable

# ------------------------------------------------------------------------------
# Integration Tests Executable
# ------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} test_integration_main.cpp ${PROJECT_INTEGRATION_TEST_FILES})
# TODO; include ${ALL_LIBRARIES} ?
target_link_libraries(${PROJECT_NAME} PRIVATE ${EXTERNAL_MODULES} "${PROJECT_SOURCE_MODULES}" glfw ${GLFW_LIBRARIES} glad ${GLAD_LIBRARIES} imgui glm stb Box2D cppfs coverage_config) #Note: see if glfw has to be included...
target_compile_definitions(${PROJECT_NAME} PRIVATE test_integration_main=main)

#TODO (1): make static / dynamic libs linking (automatic)
#TODO (2): simplify code for online test and executable target

if(MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE MSVC_PLATFORM)
endif()

if(ONLINE_MODE) # online --> move assets to CMake's default binary folder
    if(MSVC)
        message("MSVC building...")
        MoveAssetsToTarget("${CMAKE_SOURCE_DIR}\\assets" ${PROJECT_NAME})
        MoveMultipleLibsForTarget("${DYNAMIC_LIBRARIES}" ${PROJECT_NAME})
    else()
        MoveAssetsToTarget("${CMAKE_SOURCE_DIR}\\assets" ${PROJECT_NAME})
        MoveMultipleLibsForTarget("${DYNAMIC_LIBRARIES}" ${PROJECT_NAME})
    endif()
endif()

# ------------------------------------------------------------------------------
# Integration Tests: console & coverage
# ------------------------------------------------------------------------------
#add_test(${PROJECT_NAME} ${PROJECT_NAME})

CreateTest(integration test_robot)

# ------------------------------------------------------------------------------
# Integration Tests: Visual Studio
# ------------------------------------------------------------------------------
# Add tests individually if MSVC
#if(MSVC)
#    message("Import tests for MSVC environment")
#    # Note: possibility to perform a 'add_subdirectory' here and then 'CreateTest()' in that directory
#    CreateTest(test_testname) # not working with ctest on appveyor ?
#endif()