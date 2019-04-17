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

set(BUILD_SHARED_LIBS ON)
if(MSVC)
    set(BUILD_SHARED_LIBS OFF) # force STATIC builds on MSVC
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STDC_CONSTANT_MACROS")
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # for clang tidy

# Note: Must be OFF when testing (CI)
set(BUILD_EXECUTABLE_IN_PROJECT_TREE OFF)

function(MoveLibToTarget lib_name target_name)
    add_custom_command(TARGET ${target_name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:${lib_name}>"
            "$<TARGET_FILE_DIR:${target_name}>"
            VERBATIM)
    message("Moving library [${lib_name}] at target [${target_name}]")
endfunction()

function(MoveMultipleLibsForTarget libraries target_name)
    if(libraries STREQUAL "") # no input libraries (static or shared)
        message("->[Warning] In 'MoveMultipleLibsForTarget' function: no input libraries.")
    else()
        foreach(library ${libraries})
            MoveLibToTarget(${library} ${target_name})
        endforeach()
    endif()
endfunction()

macro(create_property property_name value)
    set_property(GLOBAL PROPERTY ${property_name} ${value})
endmacro()

create_property(P_PROJECT_SOURCE_MODULES "")

function(get_property_by_name output_name property_to_extract)
    get_property(property_values GLOBAL PROPERTY ${property_to_extract})
    set(${output_name} ${property_values} CACHE STRING "An extracted property's name" FORCE)
endfunction()

#TODO: function to easily set all kinds of GLOBAL properties
function(add_target_to_project module_name)
    get_property_by_name(property_output P_PROJECT_SOURCE_MODULES)
    if(property_output STREQUAL "") # empty
        set_property(GLOBAL PROPERTY P_PROJECT_SOURCE_MODULES "${module_name}")
    else() # at least one module registered
        set_property(GLOBAL PROPERTY P_PROJECT_SOURCE_MODULES "${property_output} ${module_name}")
    endif()
    message("Added target ${module_name} as a module")
endfunction()

create_property(CUSTOM_SHARED_LIBRARIES "")

#TODO: function to easily set all kinds of GLOBAL properties
function(add_data_to_property property_name module_name)
    get_property_by_name(property_output ${property_name})
    if(property_output STREQUAL "") # empty
        set_property(GLOBAL PROPERTY ${property_name} "${module_name}")
    else() # at least one module registered
        set_property(GLOBAL PROPERTY ${property_name} "${property_output} ${module_name}")
    endif()
    message("Added target ${module_name} as a module")
endfunction()

# ------------------------------------------------------------------------------
# Testing Mode: messages
# Note: Default testing mode as STANDALONE (offline)
# ------------------------------------------------------------------------------

#Note: If ONLINE OR STANDALONE_WITH_NOEXECUTABLE Then
#set(ONLINE_TESTING ON)

set(ONLINE_MODE ${ONLINE_TESTING})
if(ONLINE_MODE)
    message("Tests are configured in ONLINE mode")
else()
    message("Tests are configured in STANDALONE mode")
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static") # include gcc libs
    if(BUILD_EXECUTABLE_IN_PROJECT_TREE)
        # TODO: only apply to concerned target, as main target (ci_opengl_template) for instance
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}\\bin") # sure ?
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}\\bin") # TODO: change to lib
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}\\bin\\static") # TODO: change to lib/static

#        message("Manually copy GOOGLE TEST/MOCK shared libraries (.dll) to project binary directory to build executable directly into the project folder instead of Cmake default binary folder")
#        configure_file(${CMAKE_BINARY_DIR}/bin/libgtestd.dll ${CMAKE_SOURCE_DIR}/bin/libgtestd.dll COPYONLY)
#        configure_file(${CMAKE_BINARY_DIR}/bin/libgtest_maind.dll ${CMAKE_SOURCE_DIR}/bin/libgtest_maind.dll COPYONLY)
#        configure_file(${CMAKE_BINARY_DIR}/bin/libgmockd.dll ${CMAKE_SOURCE_DIR}/bin/libgmockd.dll COPYONLY)
#        configure_file(${CMAKE_BINARY_DIR}/bin/libgmock_maind.dll ${CMAKE_SOURCE_DIR}/bin/libgmock_maind.dll COPYONLY)
    else()
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}\\bin") # sure ?
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}\\bin") # TODO: change to lib
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}\\bin\\static") # TODO: change to lib/static
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
# Warnings
# ------------------------------------------------------------------------------
add_library(warnings_config INTERFACE)

if(MSVC)
    target_compile_options(warnings_config INTERFACE /W4)
else()
    target_compile_options(warnings_config INTERFACE -Wall -std=c++14)
    #target_compile_options(warnings_config INTERFACE -Wall -Wextra -Wpedantic -std=c++14)
endif()

# ------------------------------------------------------------------------------
# Includes
# ------------------------------------------------------------------------------
set(EXTERNALS_PATH ${CMAKE_SOURCE_DIR}/deps/externals)

#include_directories(deps) # include deps' folder. Note that you could include ${some_dep_include_dirs} from deps folder in order to be more precise at folder inclusion.
include_directories(${EXTERNALS_PATH}/glad/include)
#include_directories(deps/externals/assimp/include)
include_directories(${GLFW_SOURCE_DIR}/include) # TODO: self include this to target ?
include_directories(${EXTERNALS_PATH}/googletest/googletest/include)
include_directories(${EXTERNALS_PATH}/googletest/googlemock/include)
#include_directories(deps/externals/imgui-1.68/include)
include_directories(src)
#include_directories(assets)
include_directories(deps/externals/assimp/include)

# ------------------------------------------------------------------------------
# Dependencies (+ externals)
# ------------------------------------------------------------------------------
add_subdirectory(deps)

# ------------------------------------------------------------------------------
# Assets
# ------------------------------------------------------------------------------
add_subdirectory(assets)

# ------------------------------------------------------------------------------
# Sources
# ------------------------------------------------------------------------------
add_subdirectory(src)



get_property_by_name(PROJECT_SOURCE_MODULES P_PROJECT_SOURCE_MODULES)

message("${PROJECT_SOURCE_MODULES}")

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