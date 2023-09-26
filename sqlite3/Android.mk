# File: Android.mk
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := sqlite3
LOCAL_MODULE_FILENAME := libsqlite3

LOCAL_SRC_FILES := sqlite3.c 

include $(BUILD_STATIC_LIBRARY)
