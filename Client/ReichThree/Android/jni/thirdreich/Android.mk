LOCAL_PATH := $(call my-dir)/../../../

#加载库 libanl.a
include $(CLEAR_VARS)
LOCAL_MODULE := libanl
LOCAL_SRC_FILES := Android/obj/local/armeabi-v7a/libanl.a
include $(PREBUILD_STATIC_LIBRARY)

#加载库 libjsoncpp.a
include $(CLEAR_VARS)
LOCAL_MODULE := libjsoncpp
LOCAL_SRC_FILES := Android/obj/local/armeabi-v7a/libjsoncpp.a
include $(PREBUILD_STATIC_LIBRARY)

#加载库 libcryptopp.a
include $(CLEAR_VARS)
LOCAL_MODULE := libcryptopp
LOCAL_SRC_FILES := Android/obj/local/armeabi-v7a/libcryptopp.a
include $(PREBUILD_STATIC_LIBRARY)

#加载库 libzlib.a
include $(CLEAR_VARS)
LOCAL_MODULE := libzlib
LOCAL_SRC_FILES := Android/obj/local/armeabi-v7a/libzlib.a
include $(PREBUILD_STATIC_LIBRARY)

#加载库 libcurl.a
#include $(CLEAR_VARS)
#LOCAL_MODULE := libcurl
#LOCAL_SRC_FILES := Android/obj/local/armeabi-v7a/libcurl.a
#include $(PREBUILD_STATIC_LIBRARY)

#加载库 libprotobuf.a
include $(CLEAR_VARS)
LOCAL_MODULE := libprotobuf
LOCAL_SRC_FILES := Android/obj/local/armeabi-v7a/libprotobuf.a
include $(PREBUILD_STATIC_LIBRARY)

#加载库 libminizip.a
include $(CLEAR_VARS)
LOCAL_MODULE := libminizip
LOCAL_SRC_FILES := Android/obj/local/armeabi-v7a/libminizip.a
include $(PREBUILD_STATIC_LIBRARY)

#加载库 libbaseutil.a
include $(CLEAR_VARS)
LOCAL_MODULE := libbaseutil
LOCAL_SRC_FILES := Android/obj/local/armeabi-v7a/libbaseutil.a
include $(PREBUILD_STATIC_LIBRARY)

#加载库 libnetwork.a
include $(CLEAR_VARS)
LOCAL_MODULE := libnetwork
LOCAL_SRC_FILES := Android/obj/local/armeabi-v7a/libnetwork.a
include $(PREBUILD_STATIC_LIBRARY)

#加载库 libframework.a
include $(CLEAR_VARS)
LOCAL_MODULE := libframework
LOCAL_SRC_FILES := Android/obj/local/armeabi-v7a/libframework.a
include $(PREBUILD_STATIC_LIBRARY)

#加载库 libmsg.a
#include $(CLEAR_VARS)
#LOCAL_MODULE := libmsg
#LOCAL_SRC_FILES := Android/obj/local/armeabi-v7a/libmsg.a
#include $(PREBUILD_STATIC_LIBRARY)

#加载库 libdata.a
#include $(CLEAR_VARS)
#LOCAL_MODULE := libdata
#LOCAL_SRC_FILES := Android/obj/local/armeabi-v7a/libdata.a
#include $(PREBUILD_STATIC_LIBRARY)

#加载库 liblogic.a
#include $(CLEAR_VARS)
#LOCAL_MODULE := liblogic
#LOCAL_SRC_FILES := Android/obj/local/armeabi-v7a/liblogic.a
#include $(PREBUILD_STATIC_LIBRARY)






#生成 libthirdreich.so
include $(CLEAR_VARS)
LOCAL_MODULE := thirdreich

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
$(LOCAL_PATH)/external/libanl/source \
$(LOCAL_PATH)/external/libzlib/source \
$(LOCAL_PATH)/external/libminizip/source \
$(LOCAL_PATH)/external/libcurl/source \
$(LOCAL_PATH)/external/libjsoncpp/source \
$(LOCAL_PATH)/external/libcryptopp/source \
$(LOCAL_PATH)/external/libprotobuf/source \
$(LOCAL_PATH)/external/libprotobuf/source/src \
$(LOCAL_PATH)/external/libprotobuf/source/google/protobuf/android \
$(LOCAL_PATH)/bzbee/libbaseutil/source \
$(LOCAL_PATH)/bzbee/libframework/source \
$(LOCAL_PATH)/bzbee/libnetwork/source \
$(LOCAL_PATH)/static/static_msg \
$(LOCAL_PATH)/static/static_data \
$(LOCAL_PATH)/static/static_logic \

LOCAL_EXPORT_C_INCLUDE := $(LOCAL_PATH) \
$(LOCAL_PATH)/external/libanl/source \
$(LOCAL_PATH)/external/libzlib/source \
$(LOCAL_PATH)/external/libminizip/source \
$(LOCAL_PATH)/external/libcurl/source \
$(LOCAL_PATH)/external/libjsoncpp/source \
$(LOCAL_PATH)/external/libcryptopp/source \
$(LOCAL_PATH)/external/libprotobuf/source \
$(LOCAL_PATH)/external/libprotobuf/source/src \
$(LOCAL_PATH)/external/libprotobuf/source/google/protobuf/android \
$(LOCAL_PATH)/bzbee/libbaseutil/source \
$(LOCAL_PATH)/bzbee/libframework/source \
$(LOCAL_PATH)/bzbee/libnetwork/source \
$(LOCAL_PATH)/static/static_msg \
$(LOCAL_PATH)/static/static_data \
$(LOCAL_PATH)/static/static_logic \



#LOCAL_LDLIBS:=-L$(LOCAL_PATH)


# 赋值给NDK编译系统
LOCAL_SRC_FILES  := \




#LOCAL_SRC_FILES := $ ( foreach F, $(SRC_FILES) , $(addprefix $(dir $(F)), $(notdir $(wildcard $(LOCAL_PATH)/$(F)))))

LOCAL_STATIC_LIBRARIES := libanl \
						  libjsoncpp \
						  libzlib \
						  libprotobuf \
						  libcryptopp \
						  libminizip \
						  libbaseutil \
						  libnetwork \
						  libframework \
						  libmsg \
						  libdata \
						  liblogic \
			

						  
LOCAL_LDLIBS := -llog -lz -lm -ldl -landroid

include $(BUILD_SHARED_LIBRARY)


























