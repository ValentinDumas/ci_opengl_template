cmake_minimum_required(VERSION 3.6)
project(ci_opengl_template C CXX)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_STANDARD_REQUIRED ON) # Note: watch this carefully when coding in C.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_CXX_EXTENSIONS OFF) # Note: watch this with google test (compatibility/portability).

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

#add_definitions(-DASSIMP_BUILD_NO_IFC_IMPORTER)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message("64 bits")
    set(ARCH_64 TRUE)
else()
    message("32 bits")
    set(ARCH_64 FALSE)
endif()
if(MINGW AND ARCH_64)
    message("MINGW && 64 bits")
    add_definitions(-DENABLE_BOOST_WORKAROUND)
    add_definitions(-DASSIMP_BUILD_NO_IFC_IMPORTER)
endif()

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
# OS Specific Options
# ------------------------------------------------------------------------------
if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wa,-mbig-obj")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wa,-mbig-obj")
#option(BUILD_SHARED_LIBS ON)
#add_definitions(-DBUILD_SHARED_LIBS)




if(MSVC)
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++14")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl) # Link glad libs for Linux & Apple
    endif()
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
option(gtest_disable_pthreads "Disable uses of pthreads in gtest." ON)


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
