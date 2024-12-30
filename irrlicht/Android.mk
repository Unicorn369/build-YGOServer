# File: Android.mk
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := irrlicht

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/include \
    $(LOCAL_PATH)/source/Irrlicht

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

LOCAL_SRC_FILES := \
    source/Irrlicht/os.cpp \
    source/Irrlicht/CAttributes.cpp \
    source/Irrlicht/CFileList.cpp \
    source/Irrlicht/CFileSystem.cpp \
    source/Irrlicht/CLimitReadFile.cpp \
    source/Irrlicht/CMemoryFile.cpp \
    source/Irrlicht/CReadFile.cpp \
    source/Irrlicht/CWriteFile.cpp \
    source/Irrlicht/CXMLReader.cpp \
    source/Irrlicht/CXMLWriter.cpp \
    source/Irrlicht/CZipReader.cpp

LOCAL_CXXFLAGS := -std=gnu++11
LOCAL_CFLAGS := -Wall -pipe -fno-exceptions -fno-rtti -fstrict-aliasing
LOCAL_EXPORT_LDLIBS := -lz
LOCAL_CFLAGS += \
    -D_IRR_STATIC_LIB_ \
    -D_IRR_ANDROID_PLATFORM_ \
    -DNO_IRR_USE_NON_SYSTEM_ZLIB_ \
    -DNO_IRR_COMPILE_WITH_ZIP_ENCRYPTION_ \
    -DNO_IRR_COMPILE_WITH_BZIP2_ \
    -DNO__IRR_COMPILE_WITH_MOUNT_ARCHIVE_LOADER_ \
    -DNO__IRR_COMPILE_WITH_PAK_ARCHIVE_LOADER_ \
    -DNO__IRR_COMPILE_WITH_NPK_ARCHIVE_LOADER_ \
    -DNO__IRR_COMPILE_WITH_TAR_ARCHIVE_LOADER_ \
    -DNO__IRR_COMPILE_WITH_WAD_ARCHIVE_LOADER_

include $(BUILD_STATIC_LIBRARY)
