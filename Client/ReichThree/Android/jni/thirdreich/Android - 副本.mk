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
$(LOCAL_PATH)/external/libprotobuf/source \
$(LOCAL_PATH)/bzbee/libbaseutil/source \
$(LOCAL_PATH)/bzbee/libframework/source \
$(LOCAL_PATH)/bzbee/libnetwork/source \
$(LOCAL_PATH)/static/static_msg \
$(LOCAL_PATH)/static/static_data \
$(LOCAL_PATH)/static/static_logic \



#LOCAL_LDLIBS:=-L$(LOCAL_PATH)

SRC_FILES := $(LOCAL_PATH) \
$(LOCAL_PATH)static/static_data/*.cpp \
$(LOCAL_PATH)static/static_logic/*.cpp \

MY_FILES_PATH := $(JNI_H_INCLUDE) \
					$(LOCAL_PATH)external/libanl/source/ \
					$(LOCAL_PATH)external/libjsoncpp/source/ \
					$(LOCAL_PATH)external/libzlib/source/ \
					$(LOCAL_PATH)external/libminizip/source/ \
					$(LOCAL_PATH)static/static_msg/ \
                    $(LOCAL_PATH)static/static_data/ \
					$(LOCAL_PATH)static/static_logic/ \
					

MY_FILES_SUFFIX := %.cpp %.c %.cc

# 递归遍历目录下的所有的文件
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# 获取相应的源文件
MY_ALL_FILES := $(foreach src_path,$(MY_FILES_PATH), $(call rwildcard,$(src_path),*.*) ) 
MY_ALL_FILES := $(MY_ALL_FILES:$(MY_CPP_PATH)/./%=$(MY_CPP_PATH)%)
MY_SRC_LIST  := $(filter $(MY_FILES_SUFFIX),$(MY_ALL_FILES)) 
MY_SRC_LIST  := $(MY_SRC_LIST:$(LOCAL_PATH)/%=%)

# 去除字串的重复单词
define uniq =
  $(eval seen :=)
  $(foreach _,$1,$(if $(filter $_,${seen}),,$(eval seen += $_)))
  ${seen}
endef

# 递归遍历获取所有目录
MY_ALL_DIRS := $(dir $(foreach src_path,$(MY_FILES_PATH), $(call rwildcard,$(src_path),*/) ) )
MY_ALL_DIRS := $(call uniq,$(MY_ALL_DIRS))

# 赋值给NDK编译系统
LOCAL_SRC_FILES  := $(MY_SRC_LIST)

LOCAL_SRC_FILES += external/libprotobuf/source/google/protobuf/compiler/importer.cc \
	external/libprotobuf/source/google/protobuf/compiler/parser.cc \
	external/libprotobuf/source/google/protobuf/io/coded_stream.cc \
	external/libprotobuf/source/google/protobuf/io/gzip_stream.cc \
	external/libprotobuf/source/google/protobuf/io/printer.cc \
	external/libprotobuf/source/google/protobuf/io/strtod.cc \
	external/libprotobuf/source/google/protobuf/io/tokenizer.cc \
	external/libprotobuf/source/google/protobuf/io/zero_copy_stream.cc \
	external/libprotobuf/source/google/protobuf/io/zero_copy_stream_impl.cc \
	external/libprotobuf/source/google/protobuf/io/zero_copy_stream_impl_lite.cc \
	external/libprotobuf/source/google/protobuf/stubs/common.cc \
	external/libprotobuf/source/google/protobuf/stubs/once.cc \
	external/libprotobuf/source/google/protobuf/stubs/stringprintf.cc \
	external/libprotobuf/source/google/protobuf/stubs/structurally_valid.cc \
	external/libprotobuf/source/google/protobuf/stubs/strutil.cc \
	external/libprotobuf/source/google/protobuf/stubs/substitute.cc \
	external/libprotobuf/source/google/protobuf/text_format.cc \
	external/libprotobuf/source/google/protobuf/descriptor.cc \
	external/libprotobuf/source/google/protobuf/descriptor.pb.cc \
	external/libprotobuf/source/google/protobuf/descriptor_database.cc \
	external/libprotobuf/source/google/protobuf/dynamic_message.cc \
	external/libprotobuf/source/google/protobuf/extension_set.cc \
	external/libprotobuf/source/google/protobuf/extension_set_heavy.cc \
	external/libprotobuf/source/google/protobuf/generated_message_reflection.cc \
	external/libprotobuf/source/google/protobuf/generated_message_util.cc \
	external/libprotobuf/source/google/protobuf/message.cc \
	external/libprotobuf/source/google/protobuf/message_lite.cc \
	external/libprotobuf/source/google/protobuf/reflection_ops.cc \
	external/libprotobuf/source/google/protobuf/repeated_field.cc \
	external/libprotobuf/source/google/protobuf/service.cc \
	external/libprotobuf/source/google/protobuf/unknown_field_set.cc \
	external/libprotobuf/source/google/protobuf/wire_format.cc \
	external/libprotobuf/source/google/protobuf/wire_format_lite.cc \


LOCAL_SRC_FILES := $(filter-out $(LOCAL_PATH)external/libminizip/source/iowin32.c \
								$(LOCAL_PATH)external/libminizip/source/mztools.c, $(LOCAL_SRC_FILES))



#LOCAL_SRC_FILES := $ ( foreach F, $(SRC_FILES) , $(addprefix $(dir $(F)), $(notdir $(wildcard $(LOCAL_PATH)/$(F)))))

LOCAL_STATIC_LIBRARIES := libanl \
						  libjsoncpp \
						  libzlib \
						  libprotobuf \
						  libminizip \
						  libbaseutil \
						  libnetwork \
						  libframework \

			

						  
LOCAL_LDLIBS := -llog -lz -lm -ldl -landroid
APP_ALLOW_MISSING_DEPS=true

LOCAL_SHORT_COMMANDS := true
include $(BUILD_SHARED_LIBRARY)


























