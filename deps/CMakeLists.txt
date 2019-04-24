#create_property(ENABLE_BUILD_SHARED_LIBS OFF)
#
#macro(enable_build_shared_libs)
#    create_property(ENABLE_BUILD_SHARED_LIBS ON)
#    set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
#endmacro()
#
#macro(disable_build_shared_libs)
#    create_property(ENABLE_BUILD_SHARED_LIBS OFF)
#    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
#endmacro()
#
#get_property_by_name(s ENABLE_BUILD_SHARED_LIBS)
#message("ENABLE BUILD SHARED LIBS --> ${s}")

#
#get_property_by_name(s2 ENABLE_BUILD_SHARED_LIBS)
#message("ENABLE BUILD SHARED LIBS --> ${s2}")

create_property(P_EXTERNAL_DEPENDENCIES "")
create_property(P_PROJECT_DEPENDENCIES "")

set(TESTING_DEPENDENCIES gtest gtest_main gmock gmock_main PARENT_SCOPE)
set(EXTERNAL_DEPENDENCIES glfw ${GLFW_LIBRARIES} glad ${GLAD_LIBRARIES} glm cppfs PARENT_SCOPE)
#set(PROJECT_DEPENDENCIES ...)

if(NOT MSVC)
    set(BUILD_SHARED_LIBS ON)
endif()

# Note: Here, you can set the shared libraries' names to determine the DLLs to copy to targets
set(DYNAMIC_LIBRARIES gtest gtest_main gmock gmock_main cppfs project_src_lib PARENT_SCOPE)
set(STATIC_LIBRARIES glm_static)

add_subdirectory(externals)
