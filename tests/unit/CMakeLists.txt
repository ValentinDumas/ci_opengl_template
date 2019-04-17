project(unit_tests)

# ------------------------------------------------------------------------------
# Unit Tests Files
# ------------------------------------------------------------------------------
set(PROJECT_UNIT_TEST_FILES test_robot.cpp)

# ------------------------------------------------------------------------------
# Unit Tests Executable
# ------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} test_unit_main.cpp test_robot.cpp test_complex.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE "${EXTERNAL_MODULES}" ${PROJECT_SOURCE_MODULES} coverage_config) #Note: see if glfw has to be included...
target_compile_definitions(${PROJECT_NAME} PRIVATE test_unit_main=main)

if(MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE MSVC_PLATFORM)
endif()

if(ONLINE_MODE) # online --> move assets to CMake's default binary folder
    if(MSVC)
        message("MSVC building...")
        MoveAssetsToTarget("${CMAKE_SOURCE_DIR}\\assets" ${PROJECT_NAME})
        CopyAssets("${CMAKE_SOURCE_DIR}\\assets" "${CMAKE_CURRENT_BINARY_DIR}\\Debug")
        MoveMultipleLibsForTarget("${DYNAMIC_LIBRARIES}" ${PROJECT_NAME})
    else()
        MoveAssetsToTarget("${CMAKE_SOURCE_DIR}\\assets" ${PROJECT_NAME})
        MoveMultipleLibsForTarget("${DYNAMIC_LIBRARIES}" ${PROJECT_NAME})
    endif()
endif()
# ------------------------------------------------------------------------------
# Unit Tests: console & coverage
# ------------------------------------------------------------------------------
#add_test(${PROJECT_NAME} ${PROJECT_NAME})

CreateTest(unit test_robot)
CreateTest(unit test_complex)

# ------------------------------------------------------------------------------
# Unit Tests: Visual Studio
# ------------------------------------------------------------------------------
# Note: Add tests individually if MSVC
#if(MSVC)
#    message("Import tests for MSVC environment")
#    # Note: possibility to perform a 'add_subdirectory' here and then 'CreateTest()' in that directory
#    CreateTest(test_testname) # not working with ctest on appveyor ?
#endif()