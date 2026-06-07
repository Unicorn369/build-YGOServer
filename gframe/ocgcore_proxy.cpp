#include "../ocgcore/ocgapi.h"
#include <iostream>
#include <cstdlib>
#include <string>

// ==============================================================
// 跨平台 API 及路径宏
// ==============================================================
#ifdef _WIN32
    #include <windows.h>
    #include <io.h>
    #define ACCESS _access
    #define F_OK 0
    #define LIB_FILE_NAME "ocgcore.dll"
    typedef HMODULE LibHandle;
    #define LOAD_LIB(path) LoadLibraryA(path)
    #define GET_FUNC(handle, name) GetProcAddress(handle, name)
#else
    #include <dlfcn.h>
    #include <unistd.h>
    #include <limits.h>
    #define ACCESS access
    #ifdef __APPLE__
        #include <mach-o/dyld.h>
        #define LIB_FILE_NAME "ocgcore.bundle"
    #else
        #define LIB_FILE_NAME "libocgcore.so"
    #endif
    typedef void* LibHandle;
    #define LOAD_LIB(path) dlopen(path, RTLD_NOW)
    #define GET_FUNC(handle, name) dlsym(handle, name)
#endif

// ==============================================================
// 获取可执行文件所在绝对目录
// ==============================================================
static std::string get_executable_dir() {
    std::string path_str;
#ifdef _WIN32
    char path[MAX_PATH] = {0};
    GetModuleFileNameA(NULL, path, MAX_PATH);
    path_str = path;
    size_t pos = path_str.find_last_of("\\/");
#elif __APPLE__
    char path[PATH_MAX] = {0};
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0) {
        path_str = path;
    }
    size_t pos = path_str.find_last_of("/");
#else // Linux
    char path[PATH_MAX] = {0};
    ssize_t count = readlink("/proc/self/exe", path, PATH_MAX);
    if (count > 0) {
        path_str = std::string(path, count);
    }
    size_t pos = path_str.find_last_of("/");
#endif
    if (pos != std::string::npos) {
        return path_str.substr(0, pos); // 返回不带最后斜杠的目录
    }
    return "."; // 兜底返回当前目录
}

// ==============================================================
// 定义函数指针类型
// ==============================================================
typedef void (*PFN_set_script_reader)(script_reader f);
typedef void (*PFN_set_card_reader)(card_reader f);
typedef void (*PFN_set_message_handler)(message_handler f);
typedef intptr_t (*PFN_create_duel)(uint_fast32_t seed);
typedef intptr_t (*PFN_create_duel_v2)(uint32_t seed_sequence[]);
typedef void (*PFN_start_duel)(intptr_t pduel, uint32_t options);
typedef void (*PFN_end_duel)(intptr_t pduel);
typedef void (*PFN_set_player_info)(intptr_t pduel, int32_t playerid, int32_t lp, int32_t startcount, int32_t drawcount);
typedef void (*PFN_get_log_message)(intptr_t pduel, char* buf);
typedef int32_t (*PFN_get_message)(intptr_t pduel, byte* buf);
typedef uint32_t (*PFN_process)(intptr_t pduel);
typedef void (*PFN_new_card)(intptr_t pduel, uint32_t code, uint8_t owner, uint8_t playerid, uint8_t location, uint8_t sequence, uint8_t position);
typedef void (*PFN_new_tag_card)(intptr_t pduel, uint32_t code, uint8_t owner, uint8_t location);
typedef int32_t (*PFN_query_card)(intptr_t pduel, uint8_t playerid, uint8_t location, uint8_t sequence, uint32_t query_flag, byte* buf, int32_t use_cache);
typedef int32_t (*PFN_query_field_count)(intptr_t pduel, uint8_t playerid, uint8_t location);
typedef int32_t (*PFN_query_field_card)(intptr_t pduel, uint8_t playerid, uint8_t location, uint32_t query_flag, byte* buf, int32_t use_cache);
typedef int32_t (*PFN_query_field_info)(intptr_t pduel, byte* buf);
typedef void (*PFN_set_responsei)(intptr_t pduel, int32_t value);
typedef void (*PFN_set_responseb)(intptr_t pduel, byte* buf);
typedef int32_t (*PFN_preload_script)(intptr_t pduel, const char* script_name);
typedef byte* (*PFN_default_script_reader)(const char* script_name, int* len);

static PFN_set_script_reader dyn_set_script_reader = nullptr;
static PFN_set_card_reader dyn_set_card_reader = nullptr;
static PFN_set_message_handler dyn_set_message_handler = nullptr;
static PFN_create_duel dyn_create_duel = nullptr;
static PFN_create_duel_v2 dyn_create_duel_v2 = nullptr;
static PFN_start_duel dyn_start_duel = nullptr;
static PFN_end_duel dyn_end_duel = nullptr;
static PFN_set_player_info dyn_set_player_info = nullptr;
static PFN_get_log_message dyn_get_log_message = nullptr;
static PFN_get_message dyn_get_message = nullptr;
static PFN_process dyn_process = nullptr;
static PFN_new_card dyn_new_card = nullptr;
static PFN_new_tag_card dyn_new_tag_card = nullptr;
static PFN_query_card dyn_query_card = nullptr;
static PFN_query_field_count dyn_query_field_count = nullptr;
static PFN_query_field_card dyn_query_field_card = nullptr;
static PFN_query_field_info dyn_query_field_info = nullptr;
static PFN_set_responsei dyn_set_responsei = nullptr;
static PFN_set_responseb dyn_set_responseb = nullptr;
static PFN_preload_script dyn_preload_script = nullptr;
static PFN_default_script_reader dyn_default_script_reader = nullptr;

static LibHandle ocgcore_handle = nullptr;

// ==============================================================
// 初始化逻辑：基于程序所在目录动态构建路径
// ==============================================================
EXTERN_C void init_dynamic_ocgcore() {
    std::string exe_dir = get_executable_dir();
    std::string lib_ocgcore_path = "./updates/" + std::string(LIB_FILE_NAME);

    const char* env_ocgcore_path = getenv("LIB_OCGCORE_PATH");
    if (env_ocgcore_path) {
        lib_ocgcore_path = env_ocgcore_path;
    }

    std::string candidate_paths[] = {
        // 自定义路径
        lib_ocgcore_path,
#ifdef _WIN32
        "./YGOPro2_Data/Plugins/" + std::string(LIB_FILE_NAME),
#elif __APPLE__
        "./YGOPro2.app/Contents/Plugins/" + std::string(LIB_FILE_NAME),
#elif __LINUX__
        "./YGOPro2_Data/Plugins/x86_64/" + std::string(LIB_FILE_NAME),
#endif
        // 检查可执行文件所在目录
        exe_dir + "/" + LIB_FILE_NAME
    };

    std::string path_to_load = "";

    // 遍历检查
    for (const std::string& path : candidate_paths) {
        if (ACCESS(path.c_str(), F_OK) == 0) {
            path_to_load = path;
            //std::cout << "[YGOPro] Found library at: " << path_to_load << std::endl;
            break;
        }
    }

    if (path_to_load.empty()) {
        std::cerr << "[YGOPro] FATAL: Cannot find any " << LIB_FILE_NAME << " in CWD or Executable dir!" << std::endl;
        exit(EXIT_FAILURE);
    }

    ocgcore_handle = LOAD_LIB(path_to_load.c_str());
    if (!ocgcore_handle) {
        std::cerr << "[YGOPro] FATAL: Failed to load " << LIB_FILE_NAME << std::endl;
        exit(EXIT_FAILURE);
    }

    #define BIND_FUNC(name) dyn_##name = (PFN_##name)GET_FUNC(ocgcore_handle, #name);
    BIND_FUNC(set_script_reader);
    BIND_FUNC(set_card_reader);
    BIND_FUNC(set_message_handler);
    BIND_FUNC(create_duel);
    BIND_FUNC(create_duel_v2);
    BIND_FUNC(start_duel);
    BIND_FUNC(end_duel);
    BIND_FUNC(set_player_info);
    BIND_FUNC(get_log_message);
    BIND_FUNC(get_message);
    BIND_FUNC(process);
    BIND_FUNC(new_card);
    BIND_FUNC(new_tag_card);
    BIND_FUNC(query_card);
    BIND_FUNC(query_field_count);
    BIND_FUNC(query_field_card);
    BIND_FUNC(query_field_info);
    BIND_FUNC(set_responsei);
    BIND_FUNC(set_responseb);
    BIND_FUNC(preload_script);
    BIND_FUNC(default_script_reader);
}

// ==============================================================
// 导出 API
// ==============================================================
OCGCORE_API void set_script_reader(script_reader f) { if (dyn_set_script_reader) dyn_set_script_reader(f); }
OCGCORE_API void set_card_reader(card_reader f) { if (dyn_set_card_reader) dyn_set_card_reader(f); }
OCGCORE_API void set_message_handler(message_handler f) { if (dyn_set_message_handler) dyn_set_message_handler(f); }
OCGCORE_API intptr_t create_duel(uint_fast32_t seed) { return dyn_create_duel ? dyn_create_duel(seed) : 0; }
OCGCORE_API intptr_t create_duel_v2(uint32_t seed_sequence[]) { return dyn_create_duel_v2 ? dyn_create_duel_v2(seed_sequence) : 0; }
OCGCORE_API void start_duel(intptr_t pduel, uint32_t options) { if (dyn_start_duel) dyn_start_duel(pduel, options); }
OCGCORE_API void end_duel(intptr_t pduel) { if (dyn_end_duel) dyn_end_duel(pduel); }
OCGCORE_API void set_player_info(intptr_t pduel, int32_t playerid, int32_t lp, int32_t startcount, int32_t drawcount) { if (dyn_set_player_info) dyn_set_player_info(pduel, playerid, lp, startcount, drawcount); }
OCGCORE_API void get_log_message(intptr_t pduel, char* buf) { if (dyn_get_log_message) dyn_get_log_message(pduel, buf); }
OCGCORE_API int32_t get_message(intptr_t pduel, byte* buf) { return dyn_get_message ? dyn_get_message(pduel, buf) : 0; }
OCGCORE_API uint32_t process(intptr_t pduel) { return dyn_process ? dyn_process(pduel) : 0; }
OCGCORE_API void new_card(intptr_t pduel, uint32_t code, uint8_t owner, uint8_t playerid, uint8_t location, uint8_t sequence, uint8_t position) { if (dyn_new_card) dyn_new_card(pduel, code, owner, playerid, location, sequence, position); }
OCGCORE_API void new_tag_card(intptr_t pduel, uint32_t code, uint8_t owner, uint8_t location) { if (dyn_new_tag_card) dyn_new_tag_card(pduel, code, owner, location); }
OCGCORE_API int32_t query_card(intptr_t pduel, uint8_t playerid, uint8_t location, uint8_t sequence, uint32_t query_flag, byte* buf, int32_t use_cache) { return dyn_query_card ? dyn_query_card(pduel, playerid, location, sequence, query_flag, buf, use_cache) : 0; }
OCGCORE_API int32_t query_field_count(intptr_t pduel, uint8_t playerid, uint8_t location) { return dyn_query_field_count ? dyn_query_field_count(pduel, playerid, location) : 0; }
OCGCORE_API int32_t query_field_card(intptr_t pduel, uint8_t playerid, uint8_t location, uint32_t query_flag, byte* buf, int32_t use_cache) { return dyn_query_field_card ? dyn_query_field_card(pduel, playerid, location, query_flag, buf, use_cache) : 0; }
OCGCORE_API int32_t query_field_info(intptr_t pduel, byte* buf) { return dyn_query_field_info ? dyn_query_field_info(pduel, buf) : 0; }
OCGCORE_API void set_responsei(intptr_t pduel, int32_t value) { if (dyn_set_responsei) dyn_set_responsei(pduel, value); }
OCGCORE_API void set_responseb(intptr_t pduel, byte* buf) { if (dyn_set_responseb) dyn_set_responseb(pduel, buf); }
OCGCORE_API int32_t preload_script(intptr_t pduel, const char* script_name) { return dyn_preload_script ? dyn_preload_script(pduel, script_name) : 0; }
OCGCORE_API byte* default_script_reader(const char* script_name, int* len) { return dyn_default_script_reader ? dyn_default_script_reader(script_name, len) : nullptr; }

// 修改 gframe.cpp
//+ extern "C" void init_dynamic_ocgcore();
//
// int main(int argc, char* argv[]) {
//+    init_dynamic_ocgcore();
//
