project(unit_tests)

# ------------------------------------------------------------------------------
# UNIT TESTS: FILES
# ------------------------------------------------------------------------------
set(PROJECT_UNIT_TEST_FILES test_robot.cpp mathematics/test_complex.cpp)

set(UNIT_TESTING_DEPENDENCIES glm)

# ------------------------------------------------------------------------------
# UNIT TESTS: EXECUTABLE
# ------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} test_unit_main.cpp ${PROJECT_UNIT_TEST_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${TESTING_DEPENDENCIES} ${UNIT_TESTING_DEPENDENCIES} ${PROJECT_SOURCE_MODULES} coverage_config) #Note: see if glfw has to be included...
target_compile_definitions(${PROJECT_NAME} PRIVATE test_unit_main=main)

if(MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE MSVC_PLATFORM)
endif()

MoveNeededResourcesToTarget(${PROJECT_NAME})

# ------------------------------------------------------------------------------
# UNIT TESTS: FUNCTIONS
# ------------------------------------------------------------------------------
macro(CreateUnitTest test_name relative_test_dir)
    CreateTest(unit ${test_name} ${relative_test_dir} "${UNIT_TESTING_DEPENDENCIES}")
endmacro()

# ------------------------------------------------------------------------------
# UNIT TESTS: TESTS
# ------------------------------------------------------------------------------
# Note: Create tests from here. # (add_test(${PROJECT_NAME} ${PROJECT_NAME}))
CreateUnitTest(test_robot ${CMAKE_CURRENT_SOURCE_DIR})

# ------------------------------------------------------------------------------
# UNIT TESTS: SUB-TESTS
# ------------------------------------------------------------------------------
add_subdirectory(mathematics)