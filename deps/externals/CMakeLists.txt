# ------------------------------------------------------------------------------
# ExternalProject & Git
# ------------------------------------------------------------------------------
include(ExternalProject)
find_package(Git REQUIRED)

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
# GoogleTest / GoogleMock
# ------------------------------------------------------------------------------
add_subdirectory(googletest)

# ------------------------------------------------------------------------------
# GLad Additional Libraries
# ------------------------------------------------------------------------------
if(MSVC)
    message("CMake Platform: MSVC")
else()
    if(NOT WIN32)
        message("CMake Platform: Clang or GCC (Not Windows32) => setting additional glab library link")
        set(GLAD_LIBRARIES dl) # Link glad libs for Linux & Apple
    endif()
endif()

# ------------------------------------------------------------------------------
# GLad
# ------------------------------------------------------------------------------
add_subdirectory(glad)

# ------------------------------------------------------------------------------
# Box2D
# ------------------------------------------------------------------------------
add_subdirectory(Box2D)

# ------------------------------------------------------------------------------
# GLFW 3.2.1
# ------------------------------------------------------------------------------
option(GLFW_INSTALL OFF)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(ENABLE_BOOST_WORKAROUND OFF)
add_subdirectory(glfw_3.2.1)

# ------------------------------------------------------------------------------
# STB library
# ------------------------------------------------------------------------------
add_subdirectory(stb)

# ------------------------------------------------------------------------------
# GLM library (0.9.9.3)
# ------------------------------------------------------------------------------
option(GLM_TEST_ENABLE OFF)
option(GLM_QUIET ON) # no glm warnings
add_subdirectory(glm_0.9.9.3)

# ------------------------------------------------------------------------------
# Assimp (includes configuration with MinGW 64 bits)
# ------------------------------------------------------------------------------
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

# Assimp options
option(ENABLE_BOOST_WORKAROUND ON)
option(BUILD_SHARED_LIBS OFF)
option(BUILD_FRAMEWORK OFF)
option(ASSIMP_DOUBLE_PRECISION OFF)
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
option(BUILD DOCS OFF)

#add_subdirectory(assimp)

# ------------------------------------------------------------------------------
# Bullet
# ------------------------------------------------------------------------------
#option(BUILD_BULLET2_DEMOS OFF)
#option(BUILD_CPU_DEMOS OFF)
#option(BUILD_EXTRAS OFF)
#option(BUILD_OPENGL3_DEMOS OFF)
#option(BUILD_UNIT_TESTS OFF)
#add_subdirectory(bullet)

# ------------------------------------------------------------------------------
# CPPFS (Cross-Platform & Portable FileSystem library)
# ------------------------------------------------------------------------------
add_subdirectory(cppfs)

# ------------------------------------------------------------------------------
# ImGui
# ------------------------------------------------------------------------------
add_subdirectory(imgui-1.68)



# ------------------------------------------------------------------------------
# CppCheck
# ------------------------------------------------------------------------------
#if(ENABLE_CPPCHECK)
#
#    list(APPEND CPPCHECK_CMAKE_ARGS
#            "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
#            )
#
#    ExternalProject_Add(
#            cppcheck
#            GIT_REPOSITORY      https://github.com/danmar/cppcheck.git
#            GIT_TAG             1.79
#            GIT_SHALLOW         1
#            CMAKE_ARGS          ${CPPCHECK_CMAKE_ARGS}
#            PREFIX              ${CMAKE_BINARY_DIR}/external/cppcheck/prefix
#            TMP_DIR             ${CMAKE_BINARY_DIR}/external/cppcheck/tmp
#            STAMP_DIR           ${CMAKE_BINARY_DIR}/external/cppcheck/stamp
#            DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/cppcheck/download
#            SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/cppcheck/src
#            BINARY_DIR          ${CMAKE_BINARY_DIR}/external/cppcheck/build
#    )
#
#    list(APPEND CPPCHECK_ARGS
#            --enable=warning,style,performance,portability,unusedFunction
#            --std=c++11
#            --verbose
#            --error-exitcode=1
#            --language=c++
#            -DMAIN=main
#            -I ${CMAKE_SOURCE_DIR}/include
#            ${CMAKE_SOURCE_DIR}/include/*.h
#            ${CMAKE_SOURCE_DIR}/src/*.cpp
#            ${CMAKE_SOURCE_DIR}/tests/*.cpp
#            )
#
#    add_custom_target(
#            check
#            COMMAND ${CMAKE_BINARY_DIR}/bin/cppcheck ${CPPCHECK_ARGS}
#            COMMENT "running cppcheck"
#    )
#
#endif()

# ------------------------------------------------------------------------------
# Google Sanitizers
# ------------------------------------------------------------------------------
if(ENABLE_ASAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
endif()

if(ENABLE_USAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif()

if(ENABLE_TSAN)
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