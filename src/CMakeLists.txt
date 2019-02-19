# ------------------------------------------------------------------------------
# Custom Libraries
# ------------------------------------------------------------------------------
# Note: "glob" command -> get all .h .c .cpp files in target folders ?
add_library(project_src_lib STATIC hello.h hello.cpp)

# ------------------------------------------------------------------------------
# Main Executable
# ------------------------------------------------------------------------------
add_executable(ci_opengl_template main.cpp)
if(NOT WIN32)
    find_package(Threads)
    target_link_libraries(ci_opengl_template  glfw ${GLFW_LIBRARIES} dl glad_lib project_src_lib ${CMAKE_THREAD_LIBS_INIT})
else()
    target_link_libraries(ci_opengl_template  glfw ${GLFW_LIBRARIES} ${GLAD_LIBRARIES} glad_lib project_src_lib)
endif()