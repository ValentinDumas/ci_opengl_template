#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cppfs::cppfs" for configuration "RelWithDebInfo"
set_property(TARGET cppfs::cppfs APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(cppfs::cppfs PROPERTIES
  IMPORTED_IMPLIB_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/cppfs.lib"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/./cppfs.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS cppfs::cppfs )
list(APPEND _IMPORT_CHECK_FILES_FOR_cppfs::cppfs "${_IMPORT_PREFIX}/lib/cppfs.lib" "${_IMPORT_PREFIX}/./cppfs.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
