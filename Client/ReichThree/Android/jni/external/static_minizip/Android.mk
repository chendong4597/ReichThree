LOCAL_PATH := $(call my-dir)/../../../../external/libminizip/source
include $(CLEAR_VARS)
LOCAL_MODULE := libminizip

LOCAL_MODULE_FILENAME := libminizip

LOCAL_SRC_FILES := ioapi.c \
miniunz.c \
minizip.c \
unzip.c \
zip.c \

	
 
 
LOCAL_EXPORT_C_INCLUDES :=
LOCAL_WHOLE_STATIC_LIBRARIES := libzlib
 
LOCAL_C_INCLUDES := $(LOCAL_PATH) \
$(LOCAL_PATH)/src \
$(LOCAL_PATH)/../../../external/libzlib/source \
 
#LOCAL_LDLIBS := -llog -lz
#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)

