set(PROJECT_SOURCE_FILES complex.cpp)

add_library(project_src_lib ${PROJECT_SOURCE_FILES})

target_include_directories(project_src_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) # Note: see if it includes .hpp && .cpp OR only .cpp files

target_link_libraries(project_src_lib PUBLIC coverage_config warnings_config) # Include code-coverage & warnings settings