project(lua C CXX)

# ------------------------------------------------------------------------------
# Target Details
# ------------------------------------------------------------------------------
set(${PROJECT_NAME}_SOURCE_FILES LuaScript.cpp)

# ------------------------------------------------------------------------------
# Target Library
# ------------------------------------------------------------------------------
add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) # Note: private include directive only includes header files.

target_link_libraries(${PROJECT_NAME} PUBLIC liblua PRIVATE coverage_config warnings_config) # Include code-coverage

add_data_to_property(P_PROJECT_SOURCE_MODULES ${PROJECT_NAME})
AddLibraryToProject(${PROJECT_NAME})