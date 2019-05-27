# ------------------------------------------------------------------------------
# STB Project
# ------------------------------------------------------------------------------
project(stb)

# ------------------------------------------------------------------------------
# STB Library
# ------------------------------------------------------------------------------
# Note: STB is a header-only library, so there is no sources to add.
# We can define the library as an INTERFACE and include the headers' path
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_definitions(${PROJECT_NAME} INTERFACE STB_IMAGE_IMPLEMENTATION)

