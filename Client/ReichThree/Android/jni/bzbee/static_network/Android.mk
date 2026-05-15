LOCAL_PATH := $(call my-dir)/../../../../bzbee/libnetwork/source
include $(CLEAR_VARS)
LOCAL_MODULE := libnetwork

LOCAL_MODULE_FILENAME := libnetwork
LOCAL_SRC_FILES := MsgNetWork.pb.cc \
MsgDecoder.cpp \
MsgHandler.cpp \
DispatchMsg.cpp \
NetworkModule.cpp \
loader/ILoaderBase.cpp \
loader/HttpLoader.cpp \
loader/FileLoader.cpp \
platform/android/NetworkModule_Impl_Android.cpp \


LOCAL_WHOLE_STATIC_LIBRARIES := libbaseutil
LOCAL_WHOLE_STATIC_LIBRARIES += libframework
LOCAL_WHOLE_STATIC_LIBRARIES += libprotobuf
	
 
 
LOCAL_EXPORT_C_INCLUDES :=

LOCAL_EXPORT_LDLIBS :=
 
LOCAL_C_INCLUDES := $(LOCAL_PATH) \
$(LOCAL_PATH)/../../../bzbee/libbaseutil/source \
$(LOCAL_PATH)/../../../bzbee/libframework/source \
$(LOCAL_PATH)/../../../external/libcurl/source \
$(LOCAL_PATH)/../../../external/libprotobuf/source \

 
#LOCAL_LDLIBS := -llog -lz
#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)

