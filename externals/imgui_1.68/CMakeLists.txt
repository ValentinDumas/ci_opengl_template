project(imgui)

file(GLOB IMGUI_SOURCES *.cpp)

add_library(${PROJECT_NAME} STATIC ${IMGUI_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Include headers' root directory, so that we don't need to modify "header includes" lines in ImGui source files
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/imgui")

set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")