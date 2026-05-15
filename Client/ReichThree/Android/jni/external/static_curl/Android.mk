LOCAL_PATH := $(call my-dir)/../../../../external/libcurl/source
include $(CLEAR_VARS)
LOCAL_MODULE := libcurl

LOCAL_MODULE_FILENAME := libcurl

LOCAL_SRC_FILES :=

 
LOCAL_LDLIBS := -llog -lz
#include $(BUILD_SHARED_LIBRARY)
#include $(BUILD_STATIC_LIBRARY)

