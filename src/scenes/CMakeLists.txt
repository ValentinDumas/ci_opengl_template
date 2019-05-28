#project(scenes)
#
#file(GLOB ${PROJECT_NAME}_SOURCE_FILES "*.cpp")
#
#add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SOURCE_FILES})
#
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/.. PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
#
#target_link_libraries(${PROJECT_NAME} PRIVATE systems components entities events utils HUD)
#
#add_data_to_property(P_PROJECT_SOURCE_MODULES ${PROJECT_NAME})
#AddLibraryToProject(${PROJECT_NAME})