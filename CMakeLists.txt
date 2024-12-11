cmake_minimum_required (VERSION 3.8)
project (ygo)

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release")
endif()
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(MSVC)
    add_compile_options("/utf-8" /wd4244 /wd4267 /wd4838 /wd4577 /wd4819 /wd4018 /wd4996 /wd4477 /wd4091 /wd4828 /wd4800 /wd6011 /wd6031 /wd6054 /wd6262)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

option(SERVER_ZIP_SUPPORT "Build SERVER_ZIP_SUPPORT" ON)

add_subdirectory (gframe)
add_subdirectory (ocgcore)
add_subdirectory (libevent)
add_subdirectory (lua)
add_subdirectory (sqlite3)

if(SERVER_ZIP_SUPPORT)
    add_subdirectory (irrlicht)
    target_compile_definitions(ygopro PUBLIC -DSERVER_ZIP_SUPPORT -DSERVER_PRO2_SUPPORT)
endif()
