set(PROJECT_SOURCE_FILES complex.cpp)

add_library(project_src_lib ${PROJECT_SOURCE_FILES})

target_include_directories(project_src_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) # Note: see if it includes .hpp && .cpp OR only .cpp files

target_link_libraries(project_src_lib PUBLIC coverage_config warnings_config) # Include code-coverage & warnings settings

# ------------------------------------------------------------------------------
# Main Executable
# ------------------------------------------------------------------------------
add_executable(ci_opengl_template main.cpp)

target_link_libraries(ci_opengl_template glfw ${GLFW_LIBRARIES} glad ${GLAD_LIBRARIES} glm stb assimp::assimp Box2D project_src_lib)

target_compile_definitions(ci_opengl_template PRIVATE main=main)

# ------------------------------------------------------------------------------
# Assets
# ------------------------------------------------------------------------------
file(GLOB ASSETS assets/*)
foreach(asset ${ASSETS})
    file(COPY ${asset} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)
endforeach(asset)