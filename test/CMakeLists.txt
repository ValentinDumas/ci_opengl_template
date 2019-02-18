# ------------------------------------------------------------------------------
# Project Files
# ------------------------------------------------------------------------------
set(PROJECT_TEST_FILES test_hello.cpp)

#option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
#option(gtest_disable_pthreads "Disable uses of pthreads in gtest." ON)

# ------------------------------------------------------------------------------
# Unit Tests
# ------------------------------------------------------------------------------
if(WINDOWS)
    message("Running on windows.. do not launch tests")
else()
    add_executable(tests ${PROJECT_TEST_FILES})

    # Standard linking to gtest stuff.
    #set(THREADS_PREFER_PTHREAD_FLAG ON)
    target_link_libraries(tests PRIVATE project_src_lib gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})

    # This is so you can do 'make test' to see all your tests run, instead of
    # manually running the executable runUnitTests to see those specific tests.
    add_test(tests tests)
endif()