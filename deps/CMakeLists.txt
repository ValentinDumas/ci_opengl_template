# ------------------------------------------------------------------------------
# COVERAGE
# ------------------------------------------------------------------------------
add_library(coverage_config INTERFACE)
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
if(ENABLE_COVERAGE)
    # Add required flags (GCC & LLVM/Clang)
    target_compile_options(coverage_config INTERFACE
            -O0        # no optimization
            -g         # generate debug info
            --coverage # sets all required flags
            )
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
        target_link_options(coverage_config INTERFACE --coverage)
    else()
        target_link_libraries(coverage_config INTERFACE --coverage)
    endif()
endif(ENABLE_COVERAGE)

# ------------------------------------------------------------------------------
# WARNINGS
# ------------------------------------------------------------------------------
add_library(warnings_config INTERFACE)

if(MSVC)
    target_compile_options(warnings_config INTERFACE /W4)
else()
    target_compile_options(warnings_config INTERFACE -Wall -std=c++14)
    #target_compile_options(warnings_config INTERFACE -Wall -Wextra -Wpedantic -std=c++14)
endif()

# ------------------------------------------------------------------------------
# LIBRARIES AND OPTIONS
# ------------------------------------------------------------------------------
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

add_subdirectory(externals)




