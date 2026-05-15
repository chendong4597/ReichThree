#include $(call all-subdir-makefiles)


LOCAL_PATH := $(call my-dir)
MY_PATH := $(LOCAL_PATH)




include $(MY_PATH)/external/static_protobuf/Android.mk
include $(MY_PATH)/external/static_anl/Android.mk
include $(MY_PATH)/external/static_cryptopp/Android.mk
include $(MY_PATH)/external/static_zlib/Android.mk
include $(MY_PATH)/external/static_minizip/Android.mk
include $(MY_PATH)/external/static_jsoncpp/Android.mk
include $(MY_PATH)/bzbee/static_baseutil/Android.mk
include $(MY_PATH)/bzbee/static_framework/Android.mk
include $(MY_PATH)/bzbee/static_network/Android.mk
include $(MY_PATH)/static/static_msg/Android.mk
include $(MY_PATH)/static/static_data/Android.mk
include $(MY_PATH)/static/static_logic/Android.mk
include $(MY_PATH)/thirdreich/Android.mk


