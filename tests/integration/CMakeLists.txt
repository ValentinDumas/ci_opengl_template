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
# TODO; include ${ALL_LIBRARIES} ?
target_link_libraries(${PROJECT_NAME} PRIVATE ${TESTING_DEPENDENCIES} ${INTEGRATION_TESTING_DEPENDENCIES} "${PROJECT_SOURCE_MODULES}") #Note: see if glfw has to be included...
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
function(CreateIntegrationTest test_name relative_test_dir)
    CreateTest(integration ${test_name} ${relative_test_dir} ${INTEGRATION_TESTING_DEPENDENCIES})
endfunction()

#add_test(${PROJECT_NAME} ${PROJECT_NAME})

CreateIntegrationTest(test_robot ${CMAKE_CURRENT_SOURCE_DIR})

# ------------------------------------------------------------------------------
# Integration Tests: Visual Studio
# ------------------------------------------------------------------------------
# Add tests individually if MSVC
#if(MSVC)
#    message("Import tests for MSVC environment")
#    # Note: possibility to perform a 'add_subdirectory' here and then 'CreateTest()' in that directory
#    CreateTest(test_testname) # not working with ctest on appveyor ?
#endif()