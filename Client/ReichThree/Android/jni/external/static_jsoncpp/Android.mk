LOCAL_PATH := $(call my-dir)/../../../../external/libjsoncpp/source
include $(CLEAR_VARS)
LOCAL_MODULE := libjsoncpp

LOCAL_MODULE_FILENAME := libjsoncpp

LOCAL_SRC_FILES := json/json_reader.cpp \
json/json_value.cpp \
json/json_writer.cpp \

	
 
 
LOCAL_EXPORT_C_INCLUDES :=
LOCAL_EXPORT_LDLIBS :=
 
LOCAL_C_INCLUDES := $(LOCAL_PATH) \
 
#LOCAL_LDLIBS := -llog -lz
#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)
