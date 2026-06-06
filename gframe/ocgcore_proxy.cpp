#include "../ocgcore/ocgapi.h"
#include "ocgapi.h"
#include <iostream>
#include <cstdlib>

// ==============================================================
// 跨平台动态加载宏定义
// ==============================================================
#ifdef _WIN32
    #include <windows.h>
    #include <io.h>
    #define ACCESS _access
    #define F_OK 0
    #define UPDATE_LIB_PATH "update/ocgcore.dll"
    #define DEFAULT_LIB_PATH "ocgcore.dll"
    
    typedef HMODULE LibHandle;
    #define LOAD_LIB(path) LoadLibraryA(path)
    #define GET_FUNC(handle, name) GetProcAddress(handle, name)
    // 简单的获取错误宏，Windows 完整错误需使用 GetLastError
    #define GET_ERROR() "LoadLibrary or GetProcAddress failed" 
#else
    #include <dlfcn.h>
    #include <unistd.h>
    #define ACCESS access
    #ifdef __APPLE__
        #define UPDATE_LIB_PATH "update/libocgcore.dylib"
        #define DEFAULT_LIB_PATH "libocgcore.dylib"
    #else
        #define UPDATE_LIB_PATH "update/libocgcore.so"
        #define DEFAULT_LIB_PATH "./libocgcore.so"
    #endif
    
    typedef void* LibHandle;
    #define LOAD_LIB(path) dlopen(path, RTLD_NOW)
    #define GET_FUNC(handle, name) dlsym(handle, name)
    #define GET_ERROR() dlerror()
#endif

// ==============================================================
// 底层函数指针类型定义 (对照 ocgapi.h)
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

// ==============================================================
// 静态函数指针变量声明
// ==============================================================
static PFN_set_script_reader real_set_script_reader = nullptr;
static PFN_set_card_reader real_set_card_reader = nullptr;
static PFN_set_message_handler real_set_message_handler = nullptr;
static PFN_create_duel real_create_duel = nullptr;
static PFN_create_duel_v2 real_create_duel_v2 = nullptr;
static PFN_start_duel real_start_duel = nullptr;
static PFN_end_duel real_end_duel = nullptr;
static PFN_set_player_info real_set_player_info = nullptr;
static PFN_get_log_message real_get_log_message = nullptr;
static PFN_get_message real_get_message = nullptr;
static PFN_process real_process = nullptr;
static PFN_new_card real_new_card = nullptr;
static PFN_new_tag_card real_new_tag_card = nullptr;
static PFN_query_card real_query_card = nullptr;
static PFN_query_field_count real_query_field_count = nullptr;
static PFN_query_field_card real_query_field_card = nullptr;
static PFN_query_field_info real_query_field_info = nullptr;
static PFN_set_responsei real_set_responsei = nullptr;
static PFN_set_responseb real_set_responseb = nullptr;
static PFN_preload_script real_preload_script = nullptr;
static PFN_default_script_reader real_default_script_reader = nullptr;

static LibHandle ocgcore_handle = nullptr;

// ==============================================================
// 初始化函数 (需在 main 函数开头调用)
// ==============================================================
EXTERN_C void init_dynamic_ocgcore() {
    const char* path_to_load = DEFAULT_LIB_PATH;

    // 1. 判断 update/ocgcore.[so/dll] 是否存在
    if (ACCESS(UPDATE_LIB_PATH, F_OK) == 0) {
        std::cout << "[OCG Proxy] Detect update version, loading: " << UPDATE_LIB_PATH << std::endl;
        path_to_load = UPDATE_LIB_PATH;
    } else {
        std::cout << "[OCG Proxy] No update version, loading default: " << DEFAULT_LIB_PATH << std::endl;
    }

    // 2. 加载动态库
    ocgcore_handle = LOAD_LIB(path_to_load);
    if (!ocgcore_handle) {
        std::cerr << "[OCG Proxy] Failed to load ocgcore library! Error: " << GET_ERROR() << std::endl;
        exit(EXIT_FAILURE);
    }

    // 3. 绑定所有符号宏辅助
    #define BIND_FUNC(name) \
        real_##name = (PFN_##name)GET_FUNC(ocgcore_handle, #name); \
        if (!real_##name) std::cerr << "[OCG Proxy] Warning: Symbol '" #name "' not found in library." << std::endl;

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

    std::cout << "[OCG Proxy] Dynamic loading and binding completed successfully!" << std::endl;
}

// ==============================================================
// 拦截器/代理函数实现 (暴露给 ygopro 其他文件)
// ==============================================================
OCGCORE_API void set_script_reader(script_reader f) {
    if (real_set_script_reader) real_set_script_reader(f);
}
OCGCORE_API void set_card_reader(card_reader f) {
    if (real_set_card_reader) real_set_card_reader(f);
}
OCGCORE_API void set_message_handler(message_handler f) {
    if (real_set_message_handler) real_set_message_handler(f);
}
OCGCORE_API intptr_t create_duel(uint_fast32_t seed) {
    return real_create_duel ? real_create_duel(seed) : 0;
}
OCGCORE_API intptr_t create_duel_v2(uint32_t seed_sequence[]) {
    return real_create_duel_v2 ? real_create_duel_v2(seed_sequence) : 0;
}
OCGCORE_API void start_duel(intptr_t pduel, uint32_t options) {
    if (real_start_duel) real_start_duel(pduel, options);
}
OCGCORE_API void end_duel(intptr_t pduel) {
    if (real_end_duel) real_end_duel(pduel);
}
OCGCORE_API void set_player_info(intptr_t pduel, int32_t playerid, int32_t lp, int32_t startcount, int32_t drawcount) {
    if (real_set_player_info) real_set_player_info(pduel, playerid, lp, startcount, drawcount);
}
OCGCORE_API void get_log_message(intptr_t pduel, char* buf) {
    if (real_get_log_message) real_get_log_message(pduel, buf);
}
OCGCORE_API int32_t get_message(intptr_t pduel, byte* buf) {
    return real_get_message ? real_get_message(pduel, buf) : 0;
}
OCGCORE_API uint32_t process(intptr_t pduel) {
    return real_process ? real_process(pduel) : 0;
}
OCGCORE_API void new_card(intptr_t pduel, uint32_t code, uint8_t owner, uint8_t playerid, uint8_t location, uint8_t sequence, uint8_t position) {
    if (real_new_card) real_new_card(pduel, code, owner, playerid, location, sequence, position);
}
OCGCORE_API void new_tag_card(intptr_t pduel, uint32_t code, uint8_t owner, uint8_t location) {
    if (real_new_tag_card) real_new_tag_card(pduel, code, owner, location);
}
OCGCORE_API int32_t query_card(intptr_t pduel, uint8_t playerid, uint8_t location, uint8_t sequence, uint32_t query_flag, byte* buf, int32_t use_cache) {
    return real_query_card ? real_query_card(pduel, playerid, location, sequence, query_flag, buf, use_cache) : 0;
}
OCGCORE_API int32_t query_field_count(intptr_t pduel, uint8_t playerid, uint8_t location) {
    return real_query_field_count ? real_query_field_count(pduel, playerid, location) : 0;
}
OCGCORE_API int32_t query_field_card(intptr_t pduel, uint8_t playerid, uint8_t location, uint32_t query_flag, byte* buf, int32_t use_cache) {
    return real_query_field_card ? real_query_field_card(pduel, playerid, location, query_flag, buf, use_cache) : 0;
}
OCGCORE_API int32_t query_field_info(intptr_t pduel, byte* buf) {
    return real_query_field_info ? real_query_field_info(pduel, buf) : 0;
}
OCGCORE_API void set_responsei(intptr_t pduel, int32_t value) {
    if (real_set_responsei) real_set_responsei(pduel, value);
}
OCGCORE_API void set_responseb(intptr_t pduel, byte* buf) {
    if (real_set_responseb) real_set_responseb(pduel, buf);
}
OCGCORE_API int32_t preload_script(intptr_t pduel, const char* script_name) {
    return real_preload_script ? real_preload_script(pduel, script_name) : 0;
}
OCGCORE_API byte* default_script_reader(const char* script_name, int* len) {
    return real_default_script_reader ? real_default_script_reader(script_name, len) : nullptr;
}

//gframe.cpp
//extern "C" void init_dynamic_ocgcore();
//
//int main(int argc, char* argv[]) {
//	init_dynamic_ocgcore();
//