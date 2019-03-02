# ------------------------------------------------------------------------------
# Tests: unit
# ------------------------------------------------------------------------------
set(PROJECT_UNIT_TEST_FILES test_robot.cpp)

add_executable(unit_tests test_unit_main.cpp test_robot.cpp)
target_link_libraries(unit_tests PRIVATE ${EXTERNAL_MODULES} ${PROJECT_SOURCE_MODULES}) #Note: see if glfw has to be included...
target_compile_definitions(unit_tests PRIVATE test_unit_main=main)

CreateTest(test_complex) # not working with ctest on appveyor ?

add_test(unit_tests unit_tests)