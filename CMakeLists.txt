cmake_minimum_required(VERSION 3.6)
project(ci_opengl_template C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------------------------------------------
# Dependencies
# ------------------------------------------------------------------------------
include_directories(deps) # include deps' folder. Note that you could include ${some_dep_include_dirs} from deps folder in order to be more precise at folder inclusion.
add_subdirectory(deps)

# ------------------------------------------------------------------------------
# Sources
# ------------------------------------------------------------------------------
add_subdirectory(src)

# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------
add_subdirectory(test)