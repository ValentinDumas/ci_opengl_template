include(ExternalProject)

find_package(Git REQUIRED)

add_subdirectory(googletest)
add_subdirectory(glad)


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
add_subdirectory(glm_0.9.9.3)

# ------------------------------------------------------------------------------
# Assimp
# ------------------------------------------------------------------------------
option(ENABLE_BOOST_WORKAROUND ON)
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(BUILD_SHARED_LIBS OFF)
add_subdirectory(assimp)

# ------------------------------------------------------------------------------
# Bullet
# ------------------------------------------------------------------------------
#option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_CPU_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)
#add_subdirectory(bullet)

## ------------------------------------------------------------------------------
## Astyle
## ------------------------------------------------------------------------------
## @TODO: add -exclude=dir to astyle config and -i (ignore exclude errors)
#if(ENABLE_ASTYLE)
#
#    list(APPEND ASTYLE_CMAKE_ARGS
#            "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
#            )
#
#    ExternalProject_Add(
#            astyle
#            GIT_REPOSITORY      https://github.com/Bareflank/astyle.git
#            GIT_TAG             v1.2
#            GIT_SHALLOW         1
#            CMAKE_ARGS          ${ASTYLE_CMAKE_ARGS}
#            PREFIX              ${CMAKE_BINARY_DIR}/external/astyle/prefix
#            TMP_DIR             ${CMAKE_BINARY_DIR}/external/astyle/tmp
#            STAMP_DIR           ${CMAKE_BINARY_DIR}/external/astyle/stamp
#            DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/astyle/download
#            SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/astyle/src
#            BINARY_DIR          ${CMAKE_BINARY_DIR}/external/astyle/build
#    )
#
#    list(APPEND ASTYLE_ARGS
#            --style=1tbs
#            --lineend=linux
#            --suffix=none
#            --pad-oper
#            --unpad-paren
#            --break-closing-brackets
#            --align-pointer=name
#            --align-reference=name
#            --indent-preproc-define
#            --indent-switches
#            --indent-col1-comments
#            --keep-one-line-statements
#            --keep-one-line-blocks
#            --pad-header
#            --convert-tabs
#            --min-conditional-indent=0
#            --indent=spaces=4
#            --close-templates
#            --add-brackets
#            --ignore-exclude-errors
#            --exclude=${CMAKE_SOURCE_DIR}/deps/external/*
#            --break-after-logical
#            ${CMAKE_SOURCE_DIR}/src/*.h
#            ${CMAKE_SOURCE_DIR}/src/*.hpp
#            ${CMAKE_SOURCE_DIR}/src/*.cpp
#            )
#
#    if(NOT WIN32 STREQUAL "1")
#        add_custom_target(
#                format
#                COMMAND ${CMAKE_BINARY_DIR}/bin/astyle ${ASTYLE_ARGS}
#                COMMENT "running astyle"
#        )
#    else()
#        add_custom_target(
#                format
#                COMMAND ${CMAKE_BINARY_DIR}/bin/astyle.exe ${ASTYLE_ARGS}
#                COMMENT "running astyle"
#        )
#    endif()
#endif()

# ------------------------------------------------------------------------------
# CppCheck
# ------------------------------------------------------------------------------
if(ENABLE_CPPCHECK)

    list(APPEND CPPCHECK_CMAKE_ARGS
            "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
            )

    ExternalProject_Add(
            cppcheck
            GIT_REPOSITORY      https://github.com/danmar/cppcheck.git
            GIT_TAG             1.79
            GIT_SHALLOW         1
            CMAKE_ARGS          ${CPPCHECK_CMAKE_ARGS}
            PREFIX              ${CMAKE_BINARY_DIR}/external/cppcheck/prefix
            TMP_DIR             ${CMAKE_BINARY_DIR}/external/cppcheck/tmp
            STAMP_DIR           ${CMAKE_BINARY_DIR}/external/cppcheck/stamp
            DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/cppcheck/download
            SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/cppcheck/src
            BINARY_DIR          ${CMAKE_BINARY_DIR}/external/cppcheck/build
    )

    list(APPEND CPPCHECK_ARGS
            --enable=warning,style,performance,portability,unusedFunction
            --std=c++11
            --verbose
            --error-exitcode=1
            --language=c++
            -DMAIN=main
            -I ${CMAKE_SOURCE_DIR}/include
            ${CMAKE_SOURCE_DIR}/include/*.h
            ${CMAKE_SOURCE_DIR}/src/*.cpp
            ${CMAKE_SOURCE_DIR}/test/*.cpp
            )

    add_custom_target(
            check
            COMMAND ${CMAKE_BINARY_DIR}/bin/cppcheck ${CPPCHECK_ARGS}
            COMMENT "running cppcheck"
    )

endif()

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