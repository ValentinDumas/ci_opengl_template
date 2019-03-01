set(EXTERNAL_MODULES glm stb gtest gtest_main gmock gmock_main)
set(PROJECT_SOURCE_MODULES project_src_lib)

set(STANDALONE_TESTING ON CACHE BOOL "" FORCE) # Default testing mode as STANDALONE (offline)

if(STANDALONE_TESTING)
    message("Tests are configured in STANDALONE mode")
else()
    message("Tests are configured in ONLINE mode")
endif()

add_subdirectory(integration)
add_subdirectory(unit)
