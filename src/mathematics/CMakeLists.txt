project_as_directory_name()

set(${PROJECT_NAME}_SOURCE_FILES complex.cpp)

# TODO: write function ADD_CUSTOM_LIBRARY
# if lib i dyn

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) # Note: see if it includes .hpp && .cpp OR only .cpp files

target_link_libraries(${PROJECT_NAME} PRIVATE coverage_config warnings_config) # Include code-coverage & warnings settings

add_target_to_main_project(${PROJECT_NAME})

#add_data_to_property(P_SHARED_LIBRARIES ${PROJECT_NAME})



# TODO: look what happens when getting the property 'type' from an executable target..
# TODO: (if it's a library), get_target_properties to know if it is static or dynamic ?
# TODO: (if dynamic), add_data_to_property on P_SHARED_LIBRARIES property (previously created) -> ADD TARGET AS
# TODO:

#function(GetLibraryType )
#    set(library_type)
#
#endfunction()

#function(CREATE_CUSTOM_TARGET target_type target_name sources includes libraries)
#    set(${target_name}_SOURCE_FILES complex.cpp)
#
#        if(target_type)
#    add_library(${target_name} ${target_type} ${target_name}_SOURCE_FILES)
#
#    target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) # Note: see if it includes .hpp && .cpp OR only .cpp files
#
#    target_link_libraries(${PROJECT_NAME} PRIVATE coverage_config warnings_config) # Include code-coverage & warnings settings
#
#    add_target_to_main_project(${PROJECT_NAME})
#endfunction()
