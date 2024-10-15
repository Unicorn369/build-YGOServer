LOCAL_PATH := $(call my-dir)/../../..
#################################
USR_SHARED ?= false
#################################
include $(CLEAR_VARS)
LOCAL_MODULE := ygopro
TARGET_FORMAT_STRING_CFLAGS := 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/irrlicht/source/Irrlicht
LOCAL_C_INCLUDES += $(LOCAL_PATH)/irrlicht/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/libevent/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/lua
LOCAL_C_INCLUDES += $(LOCAL_PATH)/sqlite3

LOCAL_YGOPRO    := -DYGOPRO_SERVER_MODE -DSERVER_ZIP_SUPPORT -DSERVER_PRO2_SUPPORT
LOCAL_CFLAGS    += $(LOCAL_YGOPRO) -fno-strict-aliasing -Wno-multichar -Wno-format-security -fno-rtti
LOCAL_CXXFLAGS  := -std=c++14

LOCAL_MODULE_FILENAME := "libYGOPro.so"
#ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
#LOCAL_MODULE_FILENAME := "libYGOPro64.so"
#endif

LOCAL_SRC_FILES := \
    gframe/lzma/Alloc.c \
    gframe/lzma/LzFind.c \
    gframe/lzma/LzmaDec.c \
    gframe/lzma/LzmaEnc.c \
    gframe/lzma/LzmaLib.c \
    \
    gframe/spmemvfs/spmemvfs.c \
    \
    gframe/gframe.cpp \
    gframe/game.cpp \
    gframe/deck_manager.cpp \
    gframe/data_manager.cpp \
    gframe/replay.cpp \
    gframe/netserver.cpp \
    gframe/single_duel.cpp \
    gframe/tag_duel.cpp

LOCAL_STATIC_LIBRARIES += irrlicht
LOCAL_STATIC_LIBRARIES += libevent2_core
ifeq ($(USR_SHARED),false)
LOCAL_STATIC_LIBRARIES += libocgcore
LOCAL_STATIC_LIBRARIES += libsqlite3
else
LOCAL_LDFLAGS := @jni/LDFLAGS.txt
LOCAL_SHARED_LIBRARIES += libocgcore
LOCAL_SHARED_LIBRARIES += libsqlite3
endif

include $(BUILD_EXECUTABLE)
##############################
$(call import-add-path,$(LOCAL_PATH))
$(call import-module,irrlicht)
$(call import-module,libevent)
$(call import-module,ocgcore)
$(call import-module,sqlite3)
