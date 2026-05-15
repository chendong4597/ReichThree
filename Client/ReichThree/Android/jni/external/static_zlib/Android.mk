LOCAL_PATH := $(call my-dir)/../../../../external/libzlib/source
include $(CLEAR_VARS)
LOCAL_MODULE := libzlib

LOCAL_MODULE_FILENAME := libzlib

LOCAL_SRC_FILES := adler32.c \
compress.c \
crc32.c \
deflate.c \
gzclose.c \
gzlib.c \
gzread.c \
gzwrite.c \
infback.c \
inffast.c \
inflate.c \
inftrees.c \
trees.c \
uncompr.c \
zutil.c \



LOCAL_EXPORT_C_INCLUDE := $(LOCAL_PATH)
LOCAL_SHORT_COMMANDS := true
include $(BUILD_STATIC_LIBRARY)
