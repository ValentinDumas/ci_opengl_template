set(DYNAMIC_LIBRARIES gtest gtest_main gmock gmock_main glfw glad cppfs project_src_lib PARENT_SCOPE)
set(STATIC_LIBRARIES "" PARENT_SCOPE)
#
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

add_subdirectory(externals)
#
#get_property_by_name(s2 ENABLE_BUILD_SHARED_LIBS)
#message("ENABLE BUILD SHARED LIBS --> ${s2}")