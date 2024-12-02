# File: Android.mk
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := lua5.4
LOCAL_MODULE_FILENAME := liblua5.4
LOCAL_SRC_FILES := \
    lapi.c \
    lauxlib.c \
    lbaselib.c \
    lcode.c \
    lcorolib.c \
    lctype.c \
    ldblib.c \
    ldebug.c \
    ldo.c \
    ldump.c \
    lfunc.c \
    lgc.c \
    linit.c \
    liolib.c \
    llex.c \
    lmathlib.c \
    lmem.c \
    loadlib.c \
    lobject.c \
    lopcodes.c \
    loslib.c \
    lparser.c \
    lstate.c \
    lstring.c \
    lstrlib.c \
    ltable.c \
    ltablib.c \
    ltm.c \
    lundump.c \
    lutf8lib.c \
    lvm.c \
    lzio.c

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_CFLAGS    := -DLUA_USE_LINUX -x c++
#LOCAL_CFLAGS    := -DLUA_USE_POSIX -O2 -Wall -D"getlocaledecpoint()='.'" -fexceptions
#LOCAL_CPP_EXTENSION := .c
include $(BUILD_STATIC_LIBRARY)
