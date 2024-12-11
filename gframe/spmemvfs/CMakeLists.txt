project (spmemvfs)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} LIB_spmemvfs_SRC)
include_directories ( ../../sqlite3 )

add_library (spmemvfs STATIC ${LIB_spmemvfs_SRC})

