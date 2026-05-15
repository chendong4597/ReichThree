LOCAL_PATH := $(call my-dir)/../../../../bzbee/libframework/source
include $(CLEAR_VARS)
LOCAL_MODULE := libframework

LOCAL_MODULE_FILENAME := libframework
LOCAL_SRC_FILES := component/Component.cpp \
component/ComponentSerializer.cpp \
component/CullTree.cpp \
component/RenderableComponent.cpp \
component/SerializeFieldList.cpp \
core/ManagedObject.cpp \
core/ManagedObjectUtils.cpp \
core/ManagedInitializer.cpp \
core/ManagedClass.cpp \
core/ManagedPackage.cpp \
core/ManagedFactory.cpp \
input/TouchDelegate.cpp \
Framework.cpp \


LOCAL_WHOLE_STATIC_LIBRARIES := libbaseutil
	
 
 
LOCAL_EXPORT_C_INCLUDES :=

LOCAL_EXPORT_LDLIBS :=
 
LOCAL_C_INCLUDES := $(LOCAL_PATH) \
$(LOCAL_PATH)/../../../bzbee/libbaseutil/source \

 
#LOCAL_LDLIBS := -llog -lz
#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)

