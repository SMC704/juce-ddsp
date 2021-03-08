#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "fbjni" for configuration "Debug"
set_property(TARGET fbjni APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(fbjni PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/fbjni.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/fbjni.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS fbjni )
list(APPEND _IMPORT_CHECK_FILES_FOR_fbjni "${_IMPORT_PREFIX}/lib/fbjni.lib" "${_IMPORT_PREFIX}/bin/fbjni.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
