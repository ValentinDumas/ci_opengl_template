project(mathematics C CXX)

# ------------------------------------------------------------------------------
# Mathematics Target Details
# ------------------------------------------------------------------------------
set(${PROJECT_NAME}_SOURCE_FILES complex.cpp)

# ------------------------------------------------------------------------------
# Mathematics Target Library
# ------------------------------------------------------------------------------
add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) # Note: see if it includes .hpp && .cpp OR only .cpp files

target_link_libraries(${PROJECT_NAME} PRIVATE coverage_config) # Include code-coverage & warnings settings

add_data_to_property(P_PROJECT_SOURCE_MODULES ${PROJECT_NAME})
AddLibraryToProject(${PROJECT_NAME})