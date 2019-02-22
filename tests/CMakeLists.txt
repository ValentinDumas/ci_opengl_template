# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include" "${gmock_SOURCE_DIR}/include")
endif()

set(EXTERNAL_MODULES gtest gtest_main gmock gmock_main)
set(PROJECT_SOURCE_MODULES project_src_lib)

add_subdirectory(unit)
add_subdirectory(integration)