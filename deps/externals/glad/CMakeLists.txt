#Note: The glad version currently in use is the glad compatibility verison 3.3

add_library(glad_sources src/glad.c)

target_include_directories(glad_sources PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(NOT CMAKE_CL_64 AND NOT WIN32)
    target_compile_options(glad_sources PUBLIC -Wall -pedantic)
    #else()
    #    target_compile_options(project_src_lib PUBLIC -W4)
endif()

# Include code-coverage settings:
#target_link_libraries(glad_sources PUBLIC coverage_config)