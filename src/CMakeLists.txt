add_library(project_src_lib complex.cpp)
target_include_directories(project_src_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# Setting this to the library only avoids errors in 3rd party dependencies which are compile with e.g. -Werror
if(NOT CMAKE_CL_64 AND NOT WIN32)
    target_compile_options(project_src_lib PUBLIC -Wall -pedantic)
#else()
#    target_compile_options(project_src_lib PUBLIC -W4)
endif()

# Include code-coverage settings:
target_link_libraries(project_src_lib PUBLIC coverage_config)

# ------------------------------------------------------------------------------
# Main Executable
# ------------------------------------------------------------------------------
add_executable(ci_opengl_template main.cpp)

if(NOT CMAKE_CL_64 AND NOT WIN32) # not win64 or win32
    find_package(Threads)
    target_link_libraries(ci_opengl_template  glfw ${GLFW_LIBRARIES} dl glad_lib project_src_lib ${CMAKE_THREAD_LIBS_INIT})
else()
    target_link_libraries(ci_opengl_template  glfw ${GLFW_LIBRARIES} ${GLAD_LIBRARIES} glad_lib project_src_lib)
endif()

target_compile_definitions(ci_opengl_template PRIVATE main=main)

# WIN32
# CMAKE_CL_64
# UNIX
# MSVC