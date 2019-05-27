# ------------------------------------------------------------------------------
# GLad Project
# ------------------------------------------------------------------------------
project(glad) #Note: The glad version currently in use is the glad compatibility version 3.3

# ------------------------------------------------------------------------------
# GLad Library
# ------------------------------------------------------------------------------
add_library(${PROJECT_NAME} src/glad.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)