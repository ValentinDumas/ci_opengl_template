# ------------------------------------------------------------------------------
# Tests: unit
# ------------------------------------------------------------------------------
set(PROJECT_UNIT_TEST_FILES test_unit_main.cpp test_robot.cpp)

add_executable(unit_tests ${PROJECT_UNIT_TEST_FILES})
target_link_libraries(unit_tests PRIVATE ${EXTERNAL_MODULES} ${PROJECT_SOURCE_MODULES}) #Note: see if glfw has to be included...
target_compile_definitions(unit_tests PRIVATE main_unit_tests=main)

# This is so you can do 'make test' to see all your tests run, instead of
# manually running the executable runUnitTests to see those specific tests.
add_test(NAME unit_tests COMMAND unit_tests)

# Expose library to parent folder --> to execute ALL TESTS
add_library(unit_tests_lib STATIC ${PROJECT_UNIT_TEST_FILES})