project (ygopro)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory (lzma)
add_subdirectory (spmemvfs)

#aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_YGOPRO)

add_executable(ygopro ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(ygopro PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/gframe.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/deck_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/data_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/replay.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/netserver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/single_duel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tag_duel.cpp)

target_include_directories(ygopro PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

add_definitions(-DYGOPRO_SERVER_MODE)

target_link_libraries (ygopro clzma spmemvfs ocgcore event sqlite3)

if(WIN32)
    target_sources(ygopro PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ygopro.rc)
    target_link_libraries (ygopro ws2_32)
else()
    target_link_libraries (ygopro -ldl -lpthread)
endif()

if(SERVER_ZIP_SUPPORT)
    add_definitions(-D_IRR_WCHAR_FILESYSTEM)
    target_link_libraries(ygopro irrlicht)
    if(APPLE)
        set_target_properties(ygopro PROPERTIES OUTPUT_NAME "AI.Server.osx")
    elseif(UNIX)
        set_target_properties(ygopro PROPERTIES OUTPUT_NAME "AI.Server.linux")
    else()
        set_target_properties(ygopro PROPERTIES OUTPUT_NAME "AI.Server")
    endif()
endif()
