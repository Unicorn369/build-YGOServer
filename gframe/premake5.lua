include "lzma/."
if (SERVER_ZIP_SUPPORT or not SERVER_MODE) then
include "spmemvfs/."
end

project "ygopro"
if SERVER_MODE_DLL then
    kind "SharedLib"
else
    kind "ConsoleApp"
end
    defines { "YGOPRO_SERVER_MODE" }

    files { "gframe.cpp", "config.h",
            "game.cpp", "game.h", "myfilesystem.h",
            "deck_manager.cpp", "deck_manager.h",
            "data_manager.cpp", "data_manager.h",
            "replay.cpp", "replay.h",
            "netserver.cpp", "netserver.h",
            "single_duel.cpp", "single_duel.h",
            "tag_duel.cpp", "tag_duel.h" }
    if SERVER_MODE_DLL then
        files { "serverapi.cpp", "serverapi.h"}
    end
    includedirs { "../ocgcore" }
    links { "ocgcore", "clzma", "lua", "sqlite3", "event" }
    if SERVER_ZIP_SUPPORT then
        defines { "SERVER_ZIP_SUPPORT" }
        links { "irrlicht", "cspmemvfs", "z" }
        if BUILD_IRRLICHT then
            includedirs { "../irrlicht/source/Irrlicht" }
        end
    end
    if SERVER_PRO2_SUPPORT then
        targetname ("AI.Server")
        defines { "SERVER_PRO2_SUPPORT" }
    end

    if BUILD_EVENT then
        includedirs { "../libevent/include" }
        if os.istarget("bsd") then
            includedirs { "../libevent/bsd" }
        elseif os.istarget("macosx") then
            includedirs { "../libevent/macosx" }
        elseif os.istarget("linux") then
            includedirs { "../libevent/linux" }
        elseif os.istarget("windows") then
            includedirs { "../libevent/Win32" }
        end
    else
        includedirs { EVENT_INCLUDE_DIR }
        libdirs { EVENT_LIB_DIR }
        links { "event_pthreads" }
        --if os.istarget("windows") then
        --    links { "Bcrypt", "Iphlpapi" }
        --end
    end

    if BUILD_IRRLICHT then
        includedirs { "../irrlicht/include" }
    else
        includedirs { IRRLICHT_INCLUDE_DIR }
        libdirs { IRRLICHT_LIB_DIR }
    end

    if BUILD_FREETYPE then
        includedirs { "../freetype/include" }
    else
        includedirs { FREETYPE_INCLUDE_DIR }
        libdirs { FREETYPE_LIB_DIR }
    end

    if BUILD_SQLITE then
        includedirs { "../sqlite3" }
    else
        includedirs { SQLITE_INCLUDE_DIR }
        libdirs { SQLITE_LIB_DIR }
    end

    filter "system:windows"
        defines { "_IRR_WCHAR_FILESYSTEM" }
        files "ygopro.rc"
if not SERVER_MODE then
        libdirs { "$(DXSDK_DIR)Lib/x86" }
end
if SERVER_MODE then
        links { "ws2_32" }
else
        links { "opengl32", "ws2_32", "winmm", "gdi32", "kernel32", "user32", "imm32" }
end
    filter "not action:vs*"
        buildoptions { "-std=c++14", "-fno-rtti" }
    filter "not system:windows"
        links { "dl", "pthread" }
if not SERVER_MODE then
        links { "z" }
        defines { "GL_SILENCE_DEPRECATION" }
end
    filter "system:linux"
if not SERVER_MODE then
        links { "GL", "X11", "Xxf86vm" }
end
