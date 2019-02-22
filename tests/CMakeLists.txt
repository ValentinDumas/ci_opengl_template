set(EXTERNAL_MODULES gtest gtest_main gmock gmock_main)
set(PROJECT_SOURCE_MODULES project_src_lib)

# Default testing mode as STANDALONE (offline)
set(STANDALONE_TESTING ON CACHE BOOL "" FORCE)

add_subdirectory(integration)
add_subdirectory(unit)