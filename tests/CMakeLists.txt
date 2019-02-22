set(EXTERNAL_MODULES gtest gtest_main gmock gmock_main)
set(PROJECT_SOURCE_MODULES project_src_lib)

set(STANDALONE_TESTING ON CACHE BOOL "" FORCE) # Default testing mode as STANDALONE (offline)

if(STANDALONE_TESTING)
    message("Tests started in STANDALONE mode")
else()
    message("Tests tests started in ONLINE mode")
endif()

add_subdirectory(integration)
add_subdirectory(unit)

if(STANDALONE_TESTING) # Can execute all tests in STANDALONE mode
    add_executable(all_tests all_tests.cpp)
    target_link_libraries(all_tests PRIVATE ${EXTERNAL_MODULES} ${PROJECT_SOURCE_MODULES} ) #Note: see if glfw has to be included...
    target_compile_definitions(all_tests PRIVATE all_tests_main=main)
endif()
