#Note: The glad version currently in use is the glad compatibility version 3.3

add_library(glad_sources src/glad.c)

target_include_directories(glad_sources PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)