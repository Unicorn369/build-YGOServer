project (lua)

file(GLOB SRC_LUA "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
list(REMOVE_ITEM SRC_LUA "${CMAKE_CURRENT_SOURCE_DIR}/src/lua.c"
                         "${CMAKE_CURRENT_SOURCE_DIR}/src/luac.c"
                         "${CMAKE_CURRENT_SOURCE_DIR}/src/linit.c"
                         "${CMAKE_CURRENT_SOURCE_DIR}/src/onelua.c")

set(FLAGS "-fopenmp -Wall -Wextra -Werror")
set_source_files_properties("${SRC_LUA}" PROPERTIES COMPILE_FLAGS ${FLAGS})

if(MSVC)
    #add_compile_options(/TP)
    set_source_files_properties(${SRC_LUA} PROPERTIES LANGUAGE CXX)
else()
    add_compile_options(-x c++)
    #set_source_files_properties(${SRC_LUA} PROPERTIES LANGUAGE CXX)
endif()

if(ANDROID)
    add_compile_definitions(-DLUA_USE_POSIX)
elseif(APPLE)
    add_compile_definitions(-DLUA_USE_MACOSX)
elseif(UNIX)
    add_compile_definitions(-DLUA_USE_LINUX)
endif()

add_library (lua STATIC ${SRC_LUA})
target_include_directories(lua PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src)