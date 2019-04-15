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

if(ONLINE_MODE) # online --> move assets to CMake's default binary folder
    if(MSVC)
        message("MSVC building...")
        CopyAssets("${CMAKE_SOURCE_DIR}\\assets" "${CMAKE_CURRENT_BINARY_DIR}\\Debug")
        #        MoveAssetsToTarget("${CMAKE_SOURCE_DIR}\\assets" "${CMAKE_CURRENT_BINARY_DIR}\\Debug")
        MoveMultipleLibsForTarget("${DYNAMIC_LIBRARIES}" ${PROJECT_NAME})
        CopyAssets("${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_BINARY_DIR}\\Debug")
    else()
        MoveAssetsToTarget("${CMAKE_SOURCE_DIR}\\assets" ${PROJECT_NAME})
        MoveMultipleLibsForTarget("${DYNAMIC_LIBRARIES}" ${PROJECT_NAME})
    endif()
endif()

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