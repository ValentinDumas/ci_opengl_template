# ------------------------------------------------------------------------------
# Main Executable
# ------------------------------------------------------------------------------
set(PROJECT_SOURCE_FILES hello.cpp)

add_executable(ci_opengl_template main.cpp)

target_link_libraries(ci_opengl_template project_src_lib)