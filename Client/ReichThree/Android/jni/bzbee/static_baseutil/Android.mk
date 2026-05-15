LOCAL_PATH := $(call my-dir)/../../../../bzbee/libbaseutil/source
include $(CLEAR_VARS)
LOCAL_MODULE := libbaseutil

LOCAL_MODULE_FILENAME := libbaseutil
LOCAL_SRC_FILES := platform/android/JniHelper.cpp \
serialize/FieldAttributes.cpp \
serialize/SerializeField.cpp \
serialize/SerializeOp.cpp \
utils/BufferStream.cpp \
utils/S3MemoryDataStream.cpp \
utils/LogFile.cpp \
math/MathCommon.cpp \
math/ColourValue.cpp \
allocator/AllocCommon.cpp \
i18n/ITranslator.cpp \
i18n/Localization.cpp \
debugs/Debug.cpp \
platform/sys_threading.cpp \
lua/LuaBind.cpp \
lua/LuaCallback.cpp \
lua/ScriptVM.cpp \
lua/LuaPlus/lapi.c \
lua/LuaPlus/lauxlib.c \
lua/LuaPlus/lbaselib.c \
lua/LuaPlus/lbitlib.c \
lua/LuaPlus/lcode.c \
lua/LuaPlus/lcorolib.c \
lua/LuaPlus/lctype.c \
lua/LuaPlus/ldblib.c \
lua/LuaPlus/ldebug.c \
lua/LuaPlus/ldo.c \
lua/LuaPlus/ldump.c \
lua/LuaPlus/lfunc.c \
lua/LuaPlus/lgc.c \
lua/LuaPlus/linit.c \
lua/LuaPlus/liolib.c \
lua/LuaPlus/llex.c \
lua/LuaPlus/lmathlib.c \
lua/LuaPlus/lmem.c \
lua/LuaPlus/loadlib.c \
lua/LuaPlus/lobject.c \
lua/LuaPlus/lopcodes.c \
lua/LuaPlus/loslib.c \
lua/LuaPlus/lparser.c \
lua/LuaPlus/lstate.c \
lua/LuaPlus/lstring.c \
lua/LuaPlus/lstrlib.c \
lua/LuaPlus/ltable.c \
lua/LuaPlus/ltablib.c \
lua/LuaPlus/ltm.c \
lua/LuaPlus/lundump.c \
lua/LuaPlus/lutf8lib.c \
lua/LuaPlus/lvm.c \
lua/LuaPlus/lzio.c \
lua/LuaPlus/LuaCall.cpp \
lua/LuaPlus/LuaHelper.cpp \
lua/LuaPlus/LuaObject.cpp \
lua/LuaPlus/LuaPlus.cpp \
lua/LuaPlus/LuaPlusAddons.c \
lua/LuaPlus/LuaPlusCD.cpp \
lua/LuaPlus/LuaStackObject.cpp \
lua/LuaPlus/LuaState.cpp \
lua/LuaPlus/LuaStateCD.cpp \
lua/LuaPlus/LuaStateOutFile.cpp \
lua/LuaPlus/LuaState_DumpObject.cpp \
lua/LuaPlus/LuaStackTableIterator.cpp \
lua/LuaPlus/LuaTableIterator.cpp \
id_jobsystem/Thread.cpp \
id_jobsystem/ParallelJobList.cpp \
file/File_Zip.cpp \
file/FileSystem.cpp \
file/SubFileSystem.cpp \
file/ZipFileSystem.cpp \
base64.cpp \
BaseType.cpp \
Cache.cpp \
Cpp11EventSystem.cpp \
FileUtil.cpp \
format.cc \
platform/android/LogUtil_Android.cpp \
LogUtil.cpp \
md5.cpp \
Name.cpp \
Rtti.cpp \
StringUtil.cpp \
TextInputUtil.cpp \
platform/android/TimeUtil_Android.cpp \
platform/android/AndroidFileSystem.cpp \
platform/android/AssetFileSystem.cpp \
platform/android/File_Android.cpp \
platform/android/File_Android_Asset.cpp \
platform/android/SystemUtil_Android.cpp \
platform/android/TextInputUtil_Android.cpp \
TimeUtil.cpp \
SystemUtil.cpp \
tinyxml2.cpp \
XmlUtil.cpp \
crc_8x256_tables.cpp \
MemCrc.cpp \
RandomUtil.cpp \
GarbageCollection.cpp \
Guid.cpp \
profiler/profiler.cpp \
profiler/tracy/TracyClient.cpp \


LOCAL_WHOLE_STATIC_LIBRARIES := libminizip
LOCAL_WHOLE_STATIC_LIBRARIES += libjsoncpp
	
 
 
LOCAL_EXPORT_C_INCLUDES :=

LOCAL_EXPORT_LDLIBS :=
 
LOCAL_C_INCLUDES := $(LOCAL_PATH) \
$(LOCAL_PATH)/../../../external/libjsoncpp/source \
$(LOCAL_PATH)/../../../external/libzlib/source \
$(LOCAL_PATH)/../../../external/libminizip/source \

 
#LOCAL_LDLIBS := -llog -lz
#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)

