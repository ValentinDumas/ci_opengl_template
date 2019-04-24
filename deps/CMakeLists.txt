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

# TODO: register libraries when addind subdirectories !
# TODO: when registering a lib, GetLibraryType and add respectively to SHARED/STATIC_LIBRARIES variables, depending on the result
# TODO: Maybe, create a function ADD_SUBDIRECTORY_DEPENDENT

create_property(P_SHARED_LIBRARIES "")
create_property(P_STATIC_LIBRARIES "")
create_property(P_INTERFACE_LIBRARIES "")

function(AddLibraryToProject library_name)
    GetLibraryType(${library_name})
    #message("(AddLibraryToTarget) Library ${library_name} is a ${library_type}")
    if(library_type STREQUAL SHARED_LIBRARY)
        add_data_to_property(P_SHARED_LIBRARIES ${library_name})
    elseif(library_type STREQUAL STATIC_LIBRARY)
        add_data_to_property(P_STATIC_LIBRARIES ${library_name})
    else()
        add_data_to_property(P_INTERFACE_LIBRARIES ${library_name})
    endif()
endfunction()

# Note: Here, you can set the shared libraries' names to determine the DLLs to copy to targets
set(DYNAMIC_LIBRARIES gtest gtest_main gmock gmock_main glfw glad cppfs mathematics PARENT_SCOPE)

add_subdirectory(externals)




