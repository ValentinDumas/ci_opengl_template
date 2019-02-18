# ------------------------------------------------------------------------------
# Custom Libraries
# ------------------------------------------------------------------------------
# Note: "glob" command -> get all .h .c .cpp files in target folders ?
add_library(project_src_lib STATIC hello.h hello.cpp)

# ------------------------------------------------------------------------------
# Main Executable
# ------------------------------------------------------------------------------
add_executable(ci_opengl_template main.cpp)
target_link_libraries(ci_opengl_template project_src_lib)