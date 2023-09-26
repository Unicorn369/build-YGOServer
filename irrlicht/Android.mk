# File: Android.mk
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := irrlicht

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/include \
    $(LOCAL_PATH)/source/Irrlicht \
    $(LOCAL_PATH)/source/Irrlicht/zlib

LOCAL_SRC_FILES := \
    source/Irrlicht/zlib/adler32.c \
    source/Irrlicht/zlib/crc32.c \
    source/Irrlicht/zlib/inffast.c \
    source/Irrlicht/zlib/inflate.c \
    source/Irrlicht/zlib/inftrees.c \
    source/Irrlicht/zlib/zutil.c \
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
LOCAL_CFLAGS := -D_IRR_ANDROID_PLATFORM_ -Wall -pipe -fno-exceptions -fno-rtti -fstrict-aliasing
LOCAL_CFLAGS += \
    -D_IRR_STATIC_LIB_ \
    -DNO_IRR_COMPILE_WITH_ZIP_ENCRYPTION_ \
    -DNO_IRR_COMPILE_WITH_BZIP2_ \
    -DNO__IRR_COMPILE_WITH_MOUNT_ARCHIVE_LOADER_ \
    -DNO__IRR_COMPILE_WITH_PAK_ARCHIVE_LOADER_ \
    -DNO__IRR_COMPILE_WITH_NPK_ARCHIVE_LOADER_ \
    -DNO__IRR_COMPILE_WITH_TAR_ARCHIVE_LOADER_ \
    -DNO__IRR_COMPILE_WITH_WAD_ARCHIVE_LOADER_

include $(BUILD_STATIC_LIBRARY)
