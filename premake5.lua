-- default global settings
BUILD_LUA = true
BUILD_EVENT = true
BUILD_SQLITE = true
BUILD_IRRLICHT = true
SERVER_MODE = true
SERVER_PRO2_SUPPORT = true
SERVER_ZIP_SUPPORT = true

workspace "YGOPro"
    language "C++"

    configurations { "Release" }

    filter "system:windows"
        location "build/windows/"
        objdir "build/windows/obj"
        targetdir "build/windows/bin"
        entrypoint "mainCRTStartup"
        systemversion "latest"
        startproject "YGOPro"
        if WINXP_SUPPORT then
            defines { "WINVER=0x0501" }
            toolset "v141_xp"
        else
            defines { "WINVER=0x0601" } -- WIN7
        end

    filter "system:macosx"
        location "build/macosx/"
        objdir "build/macosx/obj"
        targetdir "build/macosx/bin"
        buildoptions { "-arch x86_64 -arch arm64" }

    filter "system:linux"
        location "build/linux/"
        objdir "build/linux/obj"
        targetdir "build/linux/bin"
        buildoptions { "-U_FORTIFY_SOURCE" }

    filter "configurations:Release"
        optimize "Speed"

    filter { "configurations:Release", "action:vs*" }
        if linktimeoptimization then
            linktimeoptimization "On"
        else
            flags { "LinkTimeOptimization" }
        end
        staticruntime "On"
        disablewarnings { "4244", "4267", "4838", "4996", "6011", "6031", "6054", "6262" }

    filter { "configurations:Release", "not action:vs*" }
        symbols "On"
        defines "NDEBUG"

    filter "action:vs*"
        cdialect "C11"
        if not WINXP_SUPPORT then
           conformancemode "On" 
        end
        vectorextensions "SSE2"
        buildoptions { "/utf-8" }
        defines { "_CRT_SECURE_NO_WARNINGS" }

    filter "not action:vs*"
        buildoptions { "-fno-strict-aliasing", "-Wno-multichar", "-Wno-format-security" }

    filter {}

    include "ocgcore"
    include "gframe"
    include "irrlicht/premake5-only-zipreader.lua"
    include "libevent"
    include "lua"
    include "sqlite3"
