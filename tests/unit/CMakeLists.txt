# ------------------------------------------------------------------------------
# Tests: unit
# ------------------------------------------------------------------------------
set(PROJECT_UNIT_TEST_FILES test_robot.cpp)

add_executable(unit_tests test_unit_main.cpp test_robot.cpp)
target_link_libraries(unit_tests PRIVATE ${EXTERNAL_MODULES} ${PROJECT_SOURCE_MODULES}) #Note: see if glfw has to be included...
target_compile_definitions(unit_tests PRIVATE test_unit_main=main)

# This is so you can do 'make test' to see all your tests run, instead of
# manually running the executable runUnitTests to see those specific tests.

if(STANDALONE_TESTING)
    message("Unit tests started in STANDALONE mode")
else()
    message("Unit tests started in ONLINE mode")
endif()

add_test(tests unit_tests)