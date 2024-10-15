LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := ocgcore
TARGET_FORMAT_STRING_CFLAGS := 

LOCAL_MODULE_FILENAME := libocgcore
LOCAL_SRC_FILES := card.cpp \
                   duel.cpp \
                   effect.cpp \
                   field.cpp \
                   group.cpp \
                   interpreter.cpp \
                   libcard.cpp \
                   libdebug.cpp \
                   libduel.cpp \
                   libeffect.cpp \
                   libgroup.cpp \
                   mem.cpp \
                   ocgapi.cpp \
                   operations.cpp \
                   playerop.cpp \
                   processor.cpp \
                   scriptlib.cpp

LOCAL_CFLAGS += -DYGOPRO_PRO2_SUPPORT
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../lua
LOCAL_STATIC_LIBRARIES += liblua5.4

ifeq ($(USR_SHARED),false)
include $(BUILD_STATIC_LIBRARY)
else
include $(BUILD_SHARED_LIBRARY)
endif
include $(LOCAL_PATH)/../lua/Android.mk
