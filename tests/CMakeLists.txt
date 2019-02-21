# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------
add_executable(tests complex_main.cpp)

target_link_libraries(tests PRIVATE gtest gtest_main glfw ${GLFW_LIBRARIES} ${GLAD_LIBRARIES} glad_lib project_src_lib)
target_compile_definitions(tests PRIVATE main_tests=main)

# This is so you can do 'make test' to see all your tests run, instead of
# manually running the executable runUnitTests to see those specific tests.
add_test(NAME main_tests COMMAND tests)
