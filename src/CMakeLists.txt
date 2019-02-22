set(PROJECT_SOURCE_FILES complex.cpp)

add_library(project_src_lib ${PROJECT_SOURCE_FILES})
target_include_directories(project_src_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) # Note: see if it includes .hpp && .cpp OR only .cpp files
# Setting this to the library only avoids errors in 3rd party dependencies which are compile with e.g. -Werror
if(NOT CMAKE_CL_64 AND NOT WIN32)
    target_compile_options(project_src_lib PUBLIC -Wall -pedantic)
#else()
#    target_compile_options(project_src_lib PUBLIC /W4)
# Note: CL=/nologo /EHsc /GR /W4 /FI "iso646.h"
endif()

# Include code-coverage settings:
target_link_libraries(project_src_lib PUBLIC coverage_config)

# ------------------------------------------------------------------------------
# Main Executable
# ------------------------------------------------------------------------------
add_executable(ci_opengl_template main.cpp)

# pthread not needed !
target_link_libraries(ci_opengl_template glfw ${GLFW_LIBRARIES} glad_sources ${GLAD_LIBRARIES} project_src_lib)

target_compile_definitions(ci_opengl_template PRIVATE main=main)

# WIN32
# CMAKE_CL_64
# UNIX
# MSVC