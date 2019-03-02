# ------------------------------------------------------------------------------
# Tests: unit
# ------------------------------------------------------------------------------
set(PROJECT_UNIT_TEST_FILES test_robot.cpp)

add_executable(unit_tests test_unit_main.cpp test_robot.cpp test_complex.cpp)
target_link_libraries(unit_tests PRIVATE ${EXTERNAL_MODULES} ${PROJECT_SOURCE_MODULES}) #Note: see if glfw has to be included...
target_compile_definitions(unit_tests PRIVATE test_unit_main=main)

add_test(unit_tests unit_tests)

# Add tests individually if MSVC
if(MSVC)
    message("Import tests for MSVC environment")
    # Note: possibility to perform a 'add_subdirectory' here and then 'CreateTest()' in that directory
    #CreateTest(test_complex) # not working with ctest on appveyor ?
endif()