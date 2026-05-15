if exist %ANDROID_NDK_ROOT%\xndk_build.bat (
call %ANDROID_NDK_ROOT%\xndk_build.bat
) else (
call %ANDROID_NDK_ROOT%\ndk-build.cmd -j NDK_DEBUG=0
)

pause