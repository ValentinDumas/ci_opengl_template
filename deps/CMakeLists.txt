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

if(NOT MSVC)
    set(BUILD_SHARED_LIBS ON)
endif()

# Note: Here, you can set the shared libraries' names to determine the DLLs to copy to targets
set(DYNAMIC_LIBRARIES gtest gtest_main gmock gmock_main glfw glad cppfs mathematics PARENT_SCOPE)

add_subdirectory(externals)
