cmake_minimum_required(VERSION 3.6)
project(ci_opengl_template C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------------------------------------------
# Dependencies
# ------------------------------------------------------------------------------
include_directories(deps) # include deps' folder. Note that you could include ${some_dep_include_dirs} from deps folder in order to be more precise at folder inclusion.
include_directories(deps/externals/glad/include)
include_directories(deps/externals/glfw_3.2.1/include)

include_directories(src)

add_subdirectory(deps)

# ------------------------------------------------------------------------------
# OS Specific Options
# ------------------------------------------------------------------------------
if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

if(MSVC)
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++14")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl) # Link glad libs for Linux & Apple
    endif()
endif()

#option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
#option(gtest_disable_pthreads "Disable uses of pthreads in gtest." ON)

# ------------------------------------------------------------------------------
# Coverage
# ------------------------------------------------------------------------------
if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()


add_library(project_src_lib STATIC src/hello.h src/hello.cpp)
# ------------------------------------------------------------------------------
# Sources
# ------------------------------------------------------------------------------
#add_subdirectory(src)
# ------------------------------------------------------------------------------
# Main Executable
# ------------------------------------------------------------------------------
add_executable(ci_opengl_template src/main.cpp)
if(NOT WIN32)
    find_package(Threads)
    target_link_libraries(ci_opengl_template  glfw ${GLFW_LIBRARIES} dl glad_lib project_src_lib ${CMAKE_THREAD_LIBS_INIT})
else()
    target_link_libraries(ci_opengl_template  glfw ${GLFW_LIBRARIES} ${GLAD_LIBRARIES} glad_lib project_src_lib)
endif()

# ------------------------------------------------------------------------------
# CTest -> testing
# ------------------------------------------------------------------------------
include(CTest) # enable_tests()


set(PROJECT_TEST_FILES test/test_hello.cpp)

# ------------------------------------------------------------------------------
# Unit Tests
# ------------------------------------------------------------------------------
if(WINDOWS)
    message("Running on windows.. do not launch tests")
else()
    add_executable(tests ${PROJECT_TEST_FILES})

    # Standard linking to gtest stuff.
    #set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads)
    target_link_libraries(tests PRIVATE gtest gtest_main ${CMAKE_THREAD_LIBS_INIT} project_src_lib)

    # This is so you can do 'make test' to see all your tests run, instead of
    # manually running the executable runUnitTests to see those specific tests.
    add_test(tests tests)
endif()


# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------
#add_subdirectory(test)