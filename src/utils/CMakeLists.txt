project(utils)

# TODO: it may be nice to separate some of the headers into "independant libraries"

# ------------------------------------------------------------------------------
# Mathematics Target Details
# ------------------------------------------------------------------------------
# ...

# ------------------------------------------------------------------------------
# Mathematics Target Library
# ------------------------------------------------------------------------------
add_library(${PROJECT_NAME} STATIC FileSystem.cpp)

target_include_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/.. PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) # Note: see if it includes .hpp && .cpp OR only .cpp files

target_link_libraries(${PROJECT_NAME} PUBLIC cppfs coverage_config) # Include code-coverage & warnings settings

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX) # Note: The line below is mandatory to find compiler language (between C / C++)

add_data_to_property(P_PROJECT_SOURCE_MODULES ${PROJECT_NAME})

AddLibraryToProject(${PROJECT_NAME})