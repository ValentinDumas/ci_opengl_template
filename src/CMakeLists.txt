project(DreamInEngine C CXX)

create_property(P_PROJECT_SOURCE_MODULES "")

# ------------------------------------------------------------------------------
# Project Modules / Libraries
# ------------------------------------------------------------------------------
add_subdirectory(lua)
add_subdirectory(utils)
add_subdirectory(mathematics)
add_subdirectory(entities)
add_subdirectory(events)
add_subdirectory(components)
add_subdirectory(systems)
#add_subdirectory(HUD)
#add_subdirectory(scenes)

set(HUD_SOURCE_FILES HUD/ImGuiHUD.cpp)
include_directories(HUD)

set(SCENES_SOURCE_FILES scenes/SceneManager.cpp scenes/Scene.cpp)
include_directories(scenes)

# ------------------------------------------------------------------------------
# Main Target Executable
# ------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} main.cpp ${HUD_SOURCE_FILES} ${SCENES_SOURCE_FILES} GLFWEnvironment.cpp ResourceManager.cpp SpriteRenderer.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} glfw glad imgui glm stb Box2D cppfs sfml-system sfml-window sfml-network sfml-graphics sfml-audio utils lua mathematics entities events components systems) # Note: pthread not needed !

MoveNeededResourcesToTarget(${PROJECT_NAME})
