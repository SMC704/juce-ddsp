#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "fbgemm" for configuration "Debug"
set_property(TARGET fbgemm APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(fbgemm PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/fbgemm.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/fbgemm.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS fbgemm )
list(APPEND _IMPORT_CHECK_FILES_FOR_fbgemm "${_IMPORT_PREFIX}/lib/fbgemm.lib" "${_IMPORT_PREFIX}/bin/fbgemm.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
