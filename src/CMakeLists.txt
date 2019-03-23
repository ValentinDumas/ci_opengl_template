set(PROJECT_SOURCE_FILES complex.cpp)

add_library(project_src_lib ${PROJECT_SOURCE_FILES})

target_include_directories(project_src_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) # Note: see if it includes .hpp && .cpp OR only .cpp files

target_link_libraries(project_src_lib PUBLIC coverage_config warnings_config) # Include code-coverage & warnings settings

# ------------------------------------------------------------------------------
# Main Executable
# ------------------------------------------------------------------------------
add_executable(ci_opengl_template imgui_main.cpp)

target_link_libraries(ci_opengl_template imgui glfw ${GLFW_LIBRARIES} glad ${GLAD_LIBRARIES} glm stb Box2D project_src_lib cppfs)
#target_link_libraries(ci_opengl_template glfw ${GLFW_LIBRARIES} glad ${GLAD_LIBRARIES} glm stb assimp::assimp Box2D project_src_lib)

if (MSVC)
    target_compile_definitions(ci_opengl_template PRIVATE main=main MSVC_PLATFORM)
else ()
    target_compile_definitions(ci_opengl_template PRIVATE main=main)
endif ()

# Note: If you want to declare source files in this scope (this cmakelists.txt) AND you want it to be visible by the parent (main cmakelists.txt),
# you must use the PARENT_SCOPE keyword as a parameter:
# set (SOURCEFILES main.cpp foo.cpp PARENT_SCOPE)
