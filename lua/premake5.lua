project "lua"
    kind "StaticLib"

    files { "*.c", "*.h", "*.hpp" }
    removefiles { "lua.c", "luac.c" }

    filter "action:vs*"
        buildoptions { "/TP" }

    filter "not action:vs*"
        buildoptions { "-x c++" }

    filter "system:bsd"
        defines { "LUA_USE_POSIX" }

    filter "system:macosx"
        defines { "LUA_USE_MACOSX" }

    filter "system:linux"
        defines { "LUA_USE_LINUX" }

    filter "system:android"
        defines { "LUA_USE_LINUX" }
