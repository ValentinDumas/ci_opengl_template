# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include" "${gmock_SOURCE_DIR}/include")
endif()

# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------
add_executable(tests complex_main.cpp test_hello.cpp)
target_link_libraries(tests PRIVATE gtest gtest_main gmock gmock_main project_src_lib) #Note: see if glfw has to be included...
target_compile_definitions(tests PRIVATE main_tests=main)

# This is so you can do 'make test' to see all your tests run, instead of
# manually running the executable runUnitTests to see those specific tests.
add_test(NAME main_tests COMMAND tests)
