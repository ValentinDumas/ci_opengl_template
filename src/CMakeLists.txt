# ------------------------------------------------------------------------------
# Main Executable
# ------------------------------------------------------------------------------
set(PROJECT_SOURCE_FILES hello.cpp)

add_executable(ci_template main.cpp)

target_link_libraries(ci_template project_src_lib)