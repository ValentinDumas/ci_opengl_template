#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cppfs::cppfs" for configuration "Debug"
set_property(TARGET cppfs::cppfs APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(cppfs::cppfs PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/cppfsd.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/./cppfsd.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS cppfs::cppfs )
list(APPEND _IMPORT_CHECK_FILES_FOR_cppfs::cppfs "${_IMPORT_PREFIX}/lib/cppfsd.lib" "${_IMPORT_PREFIX}/./cppfsd.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
