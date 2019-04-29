# ------------------------------------------------------------------------------
# File: CMakeLists.txt
# Created by Spark on 28/04/2019.
# ------------------------------------------------------------------------------

create_property(P_SHARED_LIBRARIES "")
create_property(P_STATIC_LIBRARIES "")
create_property(P_INTERFACE_LIBRARIES "")

set(BUILD_ASSIMP_LIBRARY OFF) # Note: set to ON to build the Assimp 3D Model Loader library
# set(BUILD_BULLET_LIBRARY OFF) # Note: set to ON to build the Bullet physics library

# ------------------------------------------------------------------------------
# Coverage target (interface library)
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
# Warnings target (interface library)
# ------------------------------------------------------------------------------
add_library(warnings_config INTERFACE)

if(MSVC)
    target_compile_options(warnings_config INTERFACE /W4)
else()
    #target_compile_options(warnings_config INTERFACE -Wall -std=c++14)
    target_compile_options(warnings_config INTERFACE -Wall -Wextra -Wpedantic -std=c++14)
endif()

# ------------------------------------------------------------------------------
# ExternalProject & Git
# ------------------------------------------------------------------------------
# include(ExternalProject)
# find_package(Git REQUIRED)

# ------------------------------------------------------------------------------
#
# PUT DYNAMIC LIBRARIES HERE
#
# ------------------------------------------------------------------------------
if(NOT MSVC)
    set(BUILD_SHARED_LIBS ON)
endif()
set(BUILD_SHARED_LIBS_STATUS ${BUILD_SHARED_LIBS}) # Save BUILD_SHARED_LIBS value to prevent altering it in this file

# ------------------------------------------------------------------------------
# GoogleTest / GoogleMock
# ------------------------------------------------------------------------------
set(INSTALL_GMOCK ON)
set(INSTALL_GTEST ON)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
option(gtest_disable_pthreads "Disable uses of pthreads in gtest." ON)
if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)
add_subdirectory(googletest)
AddLibraryToProject(gtest)
AddLibraryToProject(gtest_main)
AddLibraryToProject(gmock)
AddLibraryToProject(gmock_main)

# ------------------------------------------------------------------------------
# Assimp (includes configuration with MinGW 64 bits)
# ------------------------------------------------------------------------------
if(NOT BUILD_ASSIMP_LIBRARY)
    message("Assimp library build: OFF")
else()
    message("Assimp library build: ON -> Including Assimp 3D Model Loader library")
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

    ## Assimp options
    option(ENABLE_BOOST_WORKAROUND ON)
    option(BUILD_SHARED_LIBS OFF)
    option(BUILD_FRAMEWORK OFF)
    option(ASSIMP_DOUBLE_PRECISION OFF)
    option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
    option(ASSIMP_BUILD_SAMPLES OFF)
    option(ASSIMP_BUILD_TESTS OFF)
    option(BUILD DOCS OFF)

    add_subdirectory(assimp)
    AddLibraryToProject(assimp)
    target_include_directories(assimp PUBLIC ${EXTERNALS_PATH}/assimp/include)
endif()

# ------------------------------------------------------------------------------
# Bullet
# ------------------------------------------------------------------------------
#option(BUILD_BULLET2_DEMOS OFF)
#option(BUILD_CPU_DEMOS OFF)
#option(BUILD_EXTRAS OFF)
#option(BUILD_OPENGL3_DEMOS OFF)
#option(BUILD_UNIT_TESTS OFF)
#add_subdirectory(bullet)
#AddLibraryToProject(bullet)

# ------------------------------------------------------------------------------
# CPPFS (Cross-Platform & Portable FileSystem library)
# ------------------------------------------------------------------------------
add_subdirectory(cppfs)
AddLibraryToProject(cppfs)

# ------------------------------------------------------------------------------
# LuaJIT 2.0.1
# ------------------------------------------------------------------------------
add_subdirectory(luajit_2.0.3)
AddLibraryToProject(liblua)
target_include_directories(liblua PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/luajit_2.0.3/src)

# ------------------------------------------------------------------------------
#
# PUT STATIC LIBRARIES HERE
#
# ------------------------------------------------------------------------------
set(BUILD_SHARED_LIBS OFF)

# ------------------------------------------------------------------------------
# GLad
# ------------------------------------------------------------------------------
add_subdirectory(glad)
AddLibraryToProject(glad)
GetLibraryType(glad)
if (library_type STREQUAL SHARED_LIBRARY) # glad as a shared library
    # If so, define the macro GLAD_API_EXPORT on the command line.
    target_compile_definitions(glad PRIVATE GLAD_GLAPI_EXPORT)
endif()

# ------------------------------------------------------------------------------
# GLad Additional Libraries
# ------------------------------------------------------------------------------
#if(MSVC)
#    message("CMake Platform: MSVC")
#else()
#    if(NOT WIN32)
#        message("CMake Platform: Clang or GCC (Not Windows32) => setting additional glab library link")
#        set(GLAD_LIBRARIES dl) # Link glad libs for Linux & Apple
#    endif()
#endif()
#AddLibraryToProject(${GLAD_LIBRARIES})

# ------------------------------------------------------------------------------
# GLFW 3.2.1
# ------------------------------------------------------------------------------
option(GLFW_INSTALL OFF)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(ENABLE_BOOST_WORKAROUND OFF)
add_subdirectory(glfw_3.2.1)
AddLibraryToProject(glfw)
target_include_directories(glfw PUBLIC ${GLFW_SOURCE_DIR}/include)
#AddLibraryToProject(${GLFW_LIBRARIES})

# ------------------------------------------------------------------------------
# GLM library (0.9.9.3)
# ------------------------------------------------------------------------------
option(GLM_TEST_ENABLE OFF)
option(GLM_QUIET ON) # no glm warnings
add_subdirectory(glm_0.9.9.3)
AddLibraryToProject(glm)

# ------------------------------------------------------------------------------
# Box2D
# ------------------------------------------------------------------------------
add_subdirectory(Box2D)
AddLibraryToProject(Box2D)

# ------------------------------------------------------------------------------
# ImGui 1.68
# ------------------------------------------------------------------------------
add_subdirectory(imgui_1.68)
AddLibraryToProject(imgui)

#TODO: create a custom target for SFML with includes some modules of it and the "include" directory
# ------------------------------------------------------------------------------
# SFML 2.5.1
# ------------------------------------------------------------------------------
# Note: With SMFL 2.5, there is no need to add the "SFML_STATIC" definition
add_subdirectory(sfml_2.5.1)
AddLibraryToProject(sfml-system)
AddLibraryToProject(sfml-window)
AddLibraryToProject(sfml-network)
AddLibraryToProject(sfml-graphics)
AddLibraryToProject(sfml-audio)

# ------------------------------------------------------------------------------
# STB library
# ------------------------------------------------------------------------------
add_subdirectory(stb)
AddLibraryToProject(stb)

# ------------------------------------------------------------------------------
# Google Sanitizers
# ------------------------------------------------------------------------------
if(ENABLE_ASAN) # Address sanitizer
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
endif()

if(ENABLE_USAN) # Undefined sanitizer
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif()

if(ENABLE_TSAN) # Thread sanitizer
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
endif()

# ------------------------------------------------------------------------------
# Valgrind
# ------------------------------------------------------------------------------
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --leak-check=full")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --track-fds=yes")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --trace-children=yes")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --error-exitcode=1")

set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS_STATUS}) # Reset the BUILD_SHARED_LIBS value to what it was before