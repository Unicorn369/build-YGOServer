project "cspmemvfs"
    kind "StaticLib"
    cdialect "C11"
    files { "*.c", "*.h" }

    if BUILD_SQLITE then
        includedirs { "../../sqlite3" }
    else
        includedirs { SQLITE_INCLUDE_DIR }
    end

    filter "not action:vs*"
    defines { "_POSIX_C_SOURCE=200809L" }
