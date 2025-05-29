project "irrlicht"
    kind "StaticLib"

    includedirs { "include", "source/Irrlicht" }

    defines {
        "_IRR_STATIC_LIB_",
        "NO_IRR_USE_NON_SYSTEM_ZLIB_",
        "NO_IRR_COMPILE_WITH_ZIP_ENCRYPTION_",
        "NO_IRR_COMPILE_WITH_BZIP2_",
        "NO__IRR_COMPILE_WITH_MOUNT_ARCHIVE_LOADER_",
        "NO__IRR_COMPILE_WITH_PAK_ARCHIVE_LOADER_",
        "NO__IRR_COMPILE_WITH_NPK_ARCHIVE_LOADER_",
        "NO__IRR_COMPILE_WITH_TAR_ARCHIVE_LOADER_",
        "NO__IRR_COMPILE_WITH_WAD_ARCHIVE_LOADER_"
    }

    exceptionhandling "Off"
    rtti "Off"

    files { 
        "source/Irrlicht/os.cpp",
        "source/Irrlicht/CAttributes.cpp",
        "source/Irrlicht/CFileList.cpp",
        "source/Irrlicht/CFileSystem.cpp",
        "source/Irrlicht/CLimitReadFile.cpp",
        "source/Irrlicht/CMemoryFile.cpp",
        "source/Irrlicht/CReadFile.cpp",
        "source/Irrlicht/CWriteFile.cpp",
        "source/Irrlicht/CXMLReader.cpp",
        "source/Irrlicht/CXMLWriter.cpp",
        "source/Irrlicht/CZipReader.cpp"
    }

    filter { "system:windows" }
        defines { "_IRR_WCHAR_FILESYSTEM" }
