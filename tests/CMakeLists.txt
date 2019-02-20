# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------
#if(WINDOWS)
#    message("Running on windows.. do not launch tests")
#endif()
#if(NOT WINDOWS)
add_executable(tests complex_main.cpp)
#target_link_libraries(tests PRIVATE gtest gtest_main)
target_link_libraries(tests PRIVATE project_src_lib)
target_compile_definitions(tests PRIVATE main_tests=main)
add_test(NAME main_tests COMMAND tests)
    # Standard linking to gtest stuff.
    #set(THREADS_PREFER_PTHREAD_FLAG ON)
    # This is so you can do 'make test' to see all your tests run, instead of
    # manually running the executable runUnitTests to see those specific tests.
#endif()