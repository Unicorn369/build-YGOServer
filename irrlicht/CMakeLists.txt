project (irrlicht)

#aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_IRRLICHT)
add_library(irrlicht STATIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(irrlicht PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Irrlicht/os.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Irrlicht/zlib/adler32.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Irrlicht/zlib/crc32.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Irrlicht/zlib/inffast.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Irrlicht/zlib/inflate.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Irrlicht/zlib/inftrees.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Irrlicht/zlib/zutil.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Irrlicht/CAttributes.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Irrlicht/CFileList.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Irrlicht/CFileSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Irrlicht/CLimitReadFile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Irrlicht/CMemoryFile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Irrlicht/CReadFile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Irrlicht/CWriteFile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Irrlicht/CXMLReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Irrlicht/CXMLWriter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Irrlicht/CZipReader.cpp)

target_include_directories(irrlicht PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Irrlicht
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_definitions(
    -D_IRR_STATIC_LIB_
    -DNO_IRR_COMPILE_WITH_ZIP_ENCRYPTION_
    -DNO_IRR_COMPILE_WITH_BZIP2_
    -DNO__IRR_COMPILE_WITH_MOUNT_ARCHIVE_LOADER_
    -DNO__IRR_COMPILE_WITH_PAK_ARCHIVE_LOADER_
    -DNO__IRR_COMPILE_WITH_NPK_ARCHIVE_LOADER_
    -DNO__IRR_COMPILE_WITH_TAR_ARCHIVE_LOADER_
    -DNO__IRR_COMPILE_WITH_WAD_ARCHIVE_LOADER_
)

if(WIN32)
    add_definitions(-D_IRR_WCHAR_FILESYSTEM)
endif()
