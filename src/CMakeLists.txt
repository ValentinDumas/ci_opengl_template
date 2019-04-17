set(PROJECT_SRC_LIB_SOURCE_FILES complex.cpp)
add_library(project_src_lib ${PROJECT_SRC_LIB_SOURCE_FILES})
target_include_directories(project_src_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) # Note: see if it includes .hpp && .cpp OR only .cpp files
target_link_libraries(project_src_lib PRIVATE coverage_config warnings_config) # Include code-coverage & warnings settings

add_target_to_project(project_src_lib)

# ------------------------------------------------------------------------------
# Main Executable
# ------------------------------------------------------------------------------
# project(ci_opengl_template)
set(ci_opengl_template_libraries imgui glfw ${GLFW_LIBRARIES} glad ${GLAD_LIBRARIES} glm stb Box2D project_src_lib cppfs)
#set(ci_opengl_template_libraries imgui glfw ${GLFW_LIBRARIES} glad ${GLAD_LIBRARIES} glm stb Box2D project_src_lib cppfs assimp::assimp)

add_executable(ci_opengl_template imgui_main.cpp)

target_link_libraries(ci_opengl_template ${ci_opengl_template_libraries})

if (MSVC)
    target_compile_definitions(ci_opengl_template PRIVATE main=main MSVC_PLATFORM)
else ()
    target_compile_definitions(ci_opengl_template PRIVATE main=main)
endif ()

if(ONLINE_MODE) # online --> move assets to CMake's default binary folder
    if(MSVC)
        message("MSVC building...")
        # TODO: determine which "CopyAssets" call is the right one.
        CopyAssets("${CMAKE_SOURCE_DIR}\\assets" "${CMAKE_CURRENT_BINARY_DIR}\\Debug")
        #CopyAssets("${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_BINARY_DIR}\\Debug")
        MoveMultipleLibsForTarget("${DYNAMIC_LIBRARIES}" ci_opengl_template)
    else()
        MoveAssetsToTarget("${CMAKE_SOURCE_DIR}\\assets" ci_opengl_template)
        MoveMultipleLibsForTarget("${DYNAMIC_LIBRARIES}" ci_opengl_template)
    endif()

endif()

# Note: If you want to declare source files in this scope (this cmakelists.txt) AND you want it to be visible by the parent (main cmakelists.txt),
# you must use the PARENT_SCOPE keyword as a parameter:
# set (SOURCEFILES main.cpp foo.cpp PARENT_SCOPE)