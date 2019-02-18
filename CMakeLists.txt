cmake_minimum_required(VERSION 3.6)
project(ci_template C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------------------------------------------
# Includes
# ------------------------------------------------------------------------------
include_directories(deps) # Incude all dependencies & external libraries
include_directories(${PROJECT_SOURCE_DIR}/include) # current project includes
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR}) # Gtest includes

# --------------
# Call Others CMakeLists
# --------------
add_subdirectory(deps)
#add_subdirectory(include)
add_subdirectory(src)

# ------------------------------------------------------------------------------
# Custom Libraries
# ------------------------------------------------------------------------------
# Note: "glob recurse" to get all .h .c .cpp files in target folders ?
add_library(project_src_lib STATIC include/hello.h src/hello.cpp)

# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------
include(CTest) # enable_tests()
add_subdirectory(test)
