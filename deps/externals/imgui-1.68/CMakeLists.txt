project(imgui)

file(GLOB IMGUI_SOURCES *.cpp)

add_library(${PROJECT_NAME} STATIC ${IMGUI_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE glfw ${GLFW_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)