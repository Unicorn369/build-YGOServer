project (sqlite3)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_SQLITE)

add_library (sqlite3 STATIC ${SRC_SQLITE})

target_include_directories(sqlite3 PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)