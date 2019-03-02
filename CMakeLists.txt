# ------------------------------------------------------------------------------
# CMake Version
# ------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.6)

# ------------------------------------------------------------------------------
# Project: name and languages
# ------------------------------------------------------------------------------
project(ci_opengl_template C CXX)

# ------------------------------------------------------------------------------
# CMake Options
# ------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------------------------------------------
# GoogleTest configuration
# ------------------------------------------------------------------------------
# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
option(gtest_disable_pthreads "Disable uses of pthreads in gtest." ON)
if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

# ------------------------------------------------------------------------------
# Dependencies (that do not have
# ------------------------------------------------------------------------------
include_directories(deps) # include deps' folder. Note that you could include ${some_dep_include_dirs} from deps folder in order to be more precise at folder inclusion.
include_directories(deps/externals/glad/include)
include_directories(deps/externals/assimp/include)
include_directories(${GLFW_SOURCE_DIR}/include) # TODO: self include this to target ?
include_directories(deps/externals/googletest/googletest/include)
include_directories(deps/externals/googletest/googlemock/include)
include_directories(src)

add_subdirectory(deps)

# ------------------------------------------------------------------------------
# Warnings
# ------------------------------------------------------------------------------
add_library(warnings_config INTERFACE)

if(MSVC)
    target_compile_options(warnings_config INTERFACE /W4)
else()
    target_compile_options(warnings_config INTERFACE -Wall -std=c++14)
endif()

if(MSVC)
    message("CMake Platform: MSVC")
else()
    if(NOT WIN32)
        message("CMake Platform: Clang or GCC (Not Windows32) => setting additional glab library link")
        set(GLAD_LIBRARIES dl) # Link glad libs for Linux & Apple
    endif()
endif()

# ------------------------------------------------------------------------------
# Coverage
# ------------------------------------------------------------------------------
add_library(coverage_config INTERFACE)
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
if(ENABLE_COVERAGE)
    # Add required flags (GCC & LLVM/Clang)
    target_compile_options(coverage_config INTERFACE
            -O0        # no optimization
            -g         # generate debug info
            --coverage # sets all required flags
            )
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
        target_link_options(coverage_config INTERFACE --coverage)
    else()
        target_link_libraries(coverage_config INTERFACE --coverage)
    endif()
endif(ENABLE_COVERAGE)

# ------------------------------------------------------------------------------
# Sources
# ------------------------------------------------------------------------------
add_subdirectory(src)

# ------------------------------------------------------------------------------
# CTest -> testing
# ------------------------------------------------------------------------------
option (BUILD_TESTING "Build the testing tree." ON)
# Only build tests if we are the top-level project
# Allows this to be used by super projects with `add_subdirectory`
if (BUILD_TESTING AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
    include(CTest)
    add_subdirectory(tests)
endif()
