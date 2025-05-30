# File: Android.mk
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := lua5.4
LOCAL_MODULE_FILENAME := liblua5.4
LOCAL_SRC_FILES := \
    src/lapi.c \
    src/lauxlib.c \
    src/lbaselib.c \
    src/lcode.c \
    src/lcorolib.c \
    src/lctype.c \
    src/ldblib.c \
    src/ldebug.c \
    src/ldo.c \
    src/ldump.c \
    src/lfunc.c \
    src/lgc.c \
    src/liolib.c \
    src/llex.c \
    src/lmathlib.c \
    src/lmem.c \
    src/loadlib.c \
    src/lobject.c \
    src/lopcodes.c \
    src/loslib.c \
    src/lparser.c \
    src/lstate.c \
    src/lstring.c \
    src/lstrlib.c \
    src/ltable.c \
    src/ltablib.c \
    src/ltm.c \
    src/lundump.c \
    src/lutf8lib.c \
    src/lvm.c \
    src/lzio.c

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/src

LOCAL_CFLAGS    := -DLUA_USE_LINUX -x c++
#LOCAL_CFLAGS    := -DLUA_USE_POSIX -O2 -Wall -D"getlocaledecpoint()='.'" -fexceptions
#LOCAL_CPP_EXTENSION := .c
include $(BUILD_STATIC_LIBRARY)
