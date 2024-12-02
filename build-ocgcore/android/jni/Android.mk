LOCAL_PATH := $(call my-dir)/../../..

include $(CLEAR_VARS)
LOCAL_MODULE := ocgcore
TARGET_FORMAT_STRING_CFLAGS := 

LOCAL_MODULE_FILENAME := libocgcore
LOCAL_SRC_FILES := ocgcore/card.cpp \
                   ocgcore/duel.cpp \
                   ocgcore/effect.cpp \
                   ocgcore/field.cpp \
                   ocgcore/group.cpp \
                   ocgcore/interpreter.cpp \
                   ocgcore/libcard.cpp \
                   ocgcore/libdebug.cpp \
                   ocgcore/libduel.cpp \
                   ocgcore/libeffect.cpp \
                   ocgcore/libgroup.cpp \
                   ocgcore/mem.cpp \
                   ocgcore/ocgapi.cpp \
                   ocgcore/operations.cpp \
                   ocgcore/playerop.cpp \
                   ocgcore/processor.cpp \
                   ocgcore/scriptlib.cpp

LOCAL_CFLAGS += -DYGOPRO_PRO2_SUPPORT

LOCAL_STATIC_LIBRARIES += liblua5.4

include $(BUILD_SHARED_LIBRARY)
include $(LOCAL_PATH)/lua/Android.mk
