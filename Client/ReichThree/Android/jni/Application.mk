APP_STL := c++_static
APP_OPTIM := release
APP_PLATFORM := android-21
NDK_TOOLCHAIN_VERSION=4.9
APP_CPPFLAGS := -frtti -std=c++14 -pthread -fexceptions -w -fpermissive
APP_CFLAGS += -Wno-error=format-security -std=c99
APP_ABI := arm64-v8a

include $(BUILD_SHARED_LIBRARY)
