project(integration_tests)

# ------------------------------------------------------------------------------
# Integration Tests Files
# ------------------------------------------------------------------------------
set(PROJECT_INTEGRATION_TEST_FILES test_robot.cpp) # without main executable

# TODO: TEST_MODULES
# TODO: EXTERNAL_DEPENDENCIES   # from '${CMAKE_SOURCE_DIR]/deps/externals' folder
# TODO: PROJECT_DEPENDENCIES    # from '${CMAKE_SOURCE_DIR]/deps' folder

# ------------------------------------------------------------------------------
# Integration Tests Executable
# ------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} test_integration_main.cpp ${PROJECT_INTEGRATION_TEST_FILES})
# TODO; include ${ALL_LIBRARIES} ?
target_link_libraries(${PROJECT_NAME} PRIVATE "${TESTING_DEPENDENCIES}" "${EXTERNAL_DEPENDENCIES}" "${PROJECT_SOURCE_MODULES}" coverage_config) #Note: see if glfw has to be included...
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
# Note: uncommenting this is useless, it is only useful in CLion to see all tests without needing any other "CreateTest"
# ------------------------------------------------------------------------------
#add_test(${PROJECT_NAME} ${PROJECT_NAME})

# ------------------------------------------------------------------------------
# Integration Tests: Visual Studio
# ------------------------------------------------------------------------------
# Note: Add tests individually if MSVC
#if(MSVC)
CreateTest(integration test_robot)
#endif()