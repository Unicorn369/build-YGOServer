project (clzma)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} AUTO_FILES_RESULT)
add_library (clzma STATIC ${AUTO_FILES_RESULT})
