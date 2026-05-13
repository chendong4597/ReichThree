// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class ReichThree : ModuleRules
{
	public ReichThree(ReadOnlyTargetRules Target) : base(Target)
	{
        // 基础配置
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;


        //AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

        bUseUnity = true;
        if (Target.Platform == UnrealTargetPlatform.IOS)
        {

            bUseUnity = false;
            //////////////////////////////////////////////////////////////////////////


            PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "Slate", "SlateCore",
                "InputCore", "EnhancedInput", "HeadMountedDisplay", "NavigationSystem", "AIModule", "PakFile", "UMG", "AIModule",
                "Launch","TapCommon", "TapBootstrap", "TapLogin", "TapDB", "AntiAddiction"});

            string ModulePath = ModuleDirectory;

            PrivateIncludePaths.Add(Path.Combine(ModulePath, "../ReichThree"));

            string ThirdPartyPath = Path.GetFullPath(Path.Combine(ModulePath, "../../../"));
            // gets the ThirdParty folder directory path
            string ConnectorPath = ThirdPartyPath;

            string[] strExternalLibPath = { "libminizip", "libjsoncpp", "libzlib", "libcurl", "libanl", "libprotobuf", "libcryptopp" };

            for (int i = 0; i < strExternalLibPath.Length; i++)
            {
                string ConnectorIncludePath = ConnectorPath + "external/" + strExternalLibPath[i] + "/source/";
                PrivateIncludePaths.Add(ConnectorIncludePath);
            }

            string[] strBzbeeLibPath = { "libbaseutil", "libnetwork", "libframework" };

            for (int i = 0; i < strBzbeeLibPath.Length; i++)
            {
                string ConnectorIncludePath = ConnectorPath + "bzbee/" + strBzbeeLibPath[i] + "/source/";
                PrivateIncludePaths.Add(ConnectorIncludePath);
            }

            {
                string strLibPath = "static_data";// { , "static_msg" };
                string ConnectorIncludePath = ConnectorPath + "static/" + strLibPath;
                PrivateIncludePaths.Add(ConnectorIncludePath);
            }


            {
                string strLibPath = "static_msg";// { , "static_msg" };
                string ConnectorIncludePath = ConnectorPath + "static/" + strLibPath;
                PrivateIncludePaths.Add(ConnectorIncludePath);
            }

            {
                string strLibPath = "static_logic";// { , "static_msg"
                string ConnectorIncludePath = ConnectorPath + "static/" + strLibPath;
                PrivateIncludePaths.Add(ConnectorIncludePath);
            }

            {
                string ConnectorIncludePath = ConnectorPath + "Source/ReichThree";
                PrivateIncludePaths.Add(ConnectorIncludePath);
            }

            //PublicAdditionalLibraries.Add("swiftCompatibility50");

            //PublicAdditionalLibraries.Add("swiftCompatibilityDynamicReplacements");

            string SwiftLibPath = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/iphoneos";
            PublicAdditionalLibraries.Add(Path.Combine(SwiftLibPath, "libswiftCompatibility50.a"));
            PublicAdditionalLibraries.Add(Path.Combine(SwiftLibPath, "libswiftCompatibility51.a"));
            PublicAdditionalLibraries.Add(Path.Combine(SwiftLibPath, "libswiftCompatibility56.a"));
            PublicAdditionalLibraries.Add(Path.Combine(SwiftLibPath, "libswiftCompatibilityConcurrency.a"));
            PublicAdditionalLibraries.Add(Path.Combine(SwiftLibPath, "libswiftCompatibilityPacks.a"));
            PublicAdditionalLibraries.Add(Path.Combine(SwiftLibPath, "libswiftCompatibilityDynamicReplacements.a"));

            //string SwiftDyLibPath = "/Users/cd/Desktop/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift-5.0/iphoneos";

            //PublicAdditionalLibraries.Add(Path.Combine(SwiftDyLibPath, "libswiftCore.dylib"));
            //PublicAdditionalLibraries.Add(Path.Combine(SwiftDyLibPath, "libswiftCoreFoundation.dylib"));
            //PublicAdditionalLibraries.Add(Path.Combine(SwiftDyLibPath, "libswiftDispatch.dylib"));
            //PublicAdditionalLibraries.Add(Path.Combine(SwiftDyLibPath, "libswiftFoundation.dylib"));
            //PublicAdditionalLibraries.Add(Path.Combine(SwiftDyLibPath, "libswiftObjectiveC.dylib"));

            //PublicFrameworks.Add("CompositorServices");

            //string PathCom = "/Users/cd/Desktop/Xcode.app/Contents/Developer/Platforms/XROS.platform/Developer/SDKs/XROS.sdk/System/Library/Frameworks/";
            //PublicIncludePaths.Add(PathCom + "CompositorServices.framework/Headers");
            //PublicIncludePaths.Add(PathCom + "RealityKit.framework/Headers");

            //string FrameworkName = "CompositorServices.framework";
            //string FrameworkModuleName = "CompositorServices";
            //PublicAdditionalFrameworks.Add(
            //    new Framework(
            //        FrameworkModuleName,
            //        Path.Combine(PathCom, FrameworkName)
            //    )
            //);

            //PublicAdditionalFrameworks.Add(
            //    new Framework(
            //        "SwiftSystemLibraries",
            //        "/usr/lib/swift",
            //        "",
            //        true, // 标记为系统框架
            //        true  // 在远程打包时复制到Mac
            //    )
            //);

            // 添加特定的 Swift 库
            //AdditionalLinkerFlags.Add("-lswiftsys_time");
            //AdditionalLinkerFlags.Add("-lswiftFoundation");
            //AdditionalLinkerFlags.Add("-lswiftCore");

            // 添加 Swift 运行时库搜索路径
            //AdditionalLinkerFlags.Add("-L/usr/lib/swift");

            //string[] SwiftLibs = {
            //    "libswiftCore.dylib",
            //    "libswiftCoreFoundation.dylib",
            //    "libswiftDispatch.dylib",
            //    "libswiftFoundation.dylib",
            //    "libswiftObjectiveC.dylib"
            //};

            //foreach (var lib in SwiftLibs)
            //{
            //    PublicAdditionalFrameworks.Add(
            //        new Framework(
            //            lib,
            //            SwiftDyLibPath
            //        )
            //    );
            //}

            //PublicAdditionalLibraries.AddRange(new string[] {
            //    "-Wl,-rpath,@executable_path/Frameworks",
            //    "-Wl,-force_load_swift_libs",
            //    "-ObjC"
            //});

            //PublicSystemLibraryPaths.Add(SwiftLibPath);

            //{
            //    string ConnectorIncludePath = ConnectorPath + "StaticLib";
            //    PrivateIncludePaths.Add(ConnectorIncludePath);
            //}

            //{
            //    string ConnectorIncludePath = ConnectorPath + "Tap";
            //    PrivateIncludePaths.Add(ConnectorIncludePath);
            //}

            {
                //string TapPluPath = ModulePath + "../../";
                //string ConnectorIncludePath = TapPluPath + "Plugins/TapDB/Source/TapDB/Public";
                //PrivateIncludePaths.Add(ConnectorIncludePath);

                //ConnectorIncludePath = TapPluPath + "Plugins/TapBootstrap/Source/TapBootstrap/Public";
                //PrivateIncludePaths.Add(ConnectorIncludePath);

                //ConnectorIncludePath = TapPluPath + "Plugins/TapCommon/Source/TapCommon/Public";
                //PrivateIncludePaths.Add(ConnectorIncludePath);
            }

            // 启用Swift支持

            //bEnableSwift = true;

            // 添加Swift标准库的链接标志

            //AdditionalLinkerFlags.Add("-ld64");

            //AdditionalLinkerFlags.Add("-lswiftCore");

            //AdditionalLinkerFlags.Add("-lswiftQuartzCore");

            // ... 以及其他需要的库

            // 或者，如果不想一个个添加，可以尝试使用以下标志来强制加载整个Swift支持

            //AdditionalLinkerFlags.Add("-Wl,-force_load_swift_libs");
            //PrivateIncludePathModuleNames.Add("WebBrowser");
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            //PublicDefinitions.Add("_WIN32=0");
            //PublicDefinitions.Add("__ANDROID__=1");

            // 启用 AndroidX
            //PrivateDependencyModuleNames.Add("AndroidX");

            // 禁用 Jetifier（避免自动转换旧库）
            //AdditionalPropertiesForReceipt.Add("bEnableJetifier", "false");// new Dictionary<string, string>
            //AdditionalPropertiesForReceipt.Add("bUseAndroidX", "true");

            PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "Slate", "SlateCore", "InputCore", "EnhancedInput", "HeadMountedDisplay", "NavigationSystem", "AIModule", "PakFile", "UMG", "AIModule", "Launch" });

            string ModulePath = ModuleDirectory;

            //PrivateIncludePaths.Add(Path.Combine(ModulePath, "AI"));
            //PrivateIncludePaths.Add(Path.Combine(ModulePath, "Common"));
            //PrivateIncludePaths.Add(Path.Combine(ModulePath, "Config"));
            //PrivateIncludePaths.Add(Path.Combine(ModulePath, "Controls"));
            //PrivateIncludePaths.Add(Path.Combine(ModulePath, "Player"));
            //PrivateIncludePaths.Add(Path.Combine(ModulePath, "Scene"));
            //PrivateIncludePaths.Add(Path.Combine(ModulePath, "UI"));
            //PrivateIncludePaths.Add(Path.Combine(ModulePath, ""));

            string ThirdPartyPath = Path.GetFullPath(Path.Combine(ModulePath, "../../"));
            // gets the ThirdParty folder directory path
            string ConnectorPath = ThirdPartyPath;

            string[] strExternalLibPath = { "libminizip", "libjsoncpp", "libzlib", "libcurl", "libanl", "libprotobuf", "libcryptopp" };

            for (int i = 0; i < strExternalLibPath.Length; i++)
            {
                string ConnectorIncludePath = ConnectorPath + "external/" + strExternalLibPath[i] + "/source/";
                PrivateIncludePaths.Add(ConnectorIncludePath);
            }

            string[] strBzbeeLibPath = { "libbaseutil", "libnetwork", "libframework" };

            for (int i = 0; i < strBzbeeLibPath.Length; i++)
            {
                string ConnectorIncludePath = ConnectorPath + "bzbee/" + strBzbeeLibPath[i] + "/source/";
                PrivateIncludePaths.Add(ConnectorIncludePath);
            }

            {
                string strLibPath = "static_data";// { , "static_msg" };
                string ConnectorIncludePath = ConnectorPath + "static/" + strLibPath;
                PrivateIncludePaths.Add(ConnectorIncludePath);
            }


            {
                string strLibPath = "static_msg";// { , "static_msg" };
                string ConnectorIncludePath = ConnectorPath + "static/" + strLibPath;
                PrivateIncludePaths.Add(ConnectorIncludePath);
            }

            {
                string strLibPath = "static_logic";// { , "static_msg"
                string ConnectorIncludePath = ConnectorPath + "static/" + strLibPath;
                PrivateIncludePaths.Add(ConnectorIncludePath);
            }

            {
                string ConnectorIncludePath = ConnectorPath + "Source/ReichThree";
                PrivateIncludePaths.Add(ConnectorIncludePath);
            }



            //PublicAdditionalLibraries.Add(Path.Combine(ConnectorPath, "Android", "obj", "local", "armeabi-v7a", "libstatic_anl.a"));
            //PublicAdditionalLibraries.Add(Path.Combine(ConnectorPath, "Android", "obj", "local", "armeabi-v7a", "libzlib.a"));
            //PublicAdditionalLibraries.Add(Path.Combine(ConnectorPath, "Android", "obj", "local", "armeabi-v7a", "libminizip.a"));
            //PublicAdditionalLibraries.Add(Path.Combine(ConnectorPath, "Android", "obj", "local", "armeabi-v7a", "libjsoncpp.a"));
            //PublicAdditionalLibraries.Add(Path.Combine(ConnectorPath, "Android", "obj", "local", "armeabi-v7a", "libcurl.a"));
            //PublicAdditionalLibraries.Add(Path.Combine(ConnectorPath, "Android", "obj", "local", "armeabi-v7a", "libprotobuf.a"));
            //PublicAdditionalLibraries.Add(Path.Combine(ConnectorPath, "Android", "obj", "local", "armeabi-v7a", "libbaseutil.a"));
            //PublicAdditionalLibraries.Add(Path.Combine(ConnectorPath, "Android", "obj", "local", "armeabi-v7a", "libframework.a"));
            //PublicAdditionalLibraries.Add(Path.Combine(ConnectorPath, "Android", "obj", "local", "armeabi-v7a", "libnetwork.a"));
            //PublicAdditionalLibraries.Add(Path.Combine(ConnectorPath, "Android", "obj", "local", "armeabi-v7a", "libmsg.a"));
            //PublicAdditionalLibraries.Add(Path.Combine(ConnectorPath, "Android", "obj", "local", "armeabi-v7a", "libdata.a"));
            //PublicAdditionalLibraries.Add(Path.Combine(ConnectorPath, "Android", "obj", "local", "armeabi-v7a", "liblogic.a"));

            //PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });

            //PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "..", "..", "build", "Android", "taptap", "tap-core-4.5.4.aar"));
            //PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "..", "..", "build", "Android", "taptap", "tap-kit-4.5.4.aar"));
            //PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "..", "..", "build", "Android", "taptap", "tap-login-4.5.4.aar"));

            // AdditionalPropertiesForReceipt.Add(
            //    "AndroidPlugin",
            //    Path.Combine(ModuleDirectory, "taptap.xml")
            //);

            //AdditionalPropertiesForReceipt.Add(
            //    "AdditionalPropertiesForAndroid",
            //    "implementation 'com.taptap.sdk:tap-core:4.5.5'"
            //);

            //ConfiggurePro = ProguardConfiguration.Create(
            //"-keepclassmembers class com.wskj.ThirdReich.TaptapUtils {\r\n\tpublic *;\r\n}\n" +
            //"-keepclassmembers class com.wskj.ThirdReich.TaptapNative {\r\n\tpublic *;\r\n}\n" +
            //"-keepclasseswithmembernames class * {\r\n    native <methods>;\r\n}\n" +
            //"-keepclasseswithmembernames class * {\r\n    public native void Java_*;\r\n}\n"
            // );
        }
        else
        {
            PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "Slate", "SlateCore", "InputCore",
                "EnhancedInput", "HeadMountedDisplay", "NavigationSystem", "AIModule", "PakFile", "UMG", "AIModule", "OnlineSubsystem",
                "OnlineSubsystemSteam"});

            PublicDefinitions.Add("FMT_GCC_VERSION=11"); // 根据实际 GCC 版本修改
            PublicDefinitions.Add("PLATFORM_HTML5=1");
            PublicDefinitions.Add("FMT_USE_NOEXCEPT=1");
            PublicDefinitions.Add("FMT_USE_DELETED_FUNCTIONS=1");
            PublicDefinitions.Add("LUA_VERSION_NUM=1");

            string ModulePath = ModuleDirectory;

            string ThirdPartyPath = Path.GetFullPath(Path.Combine(ModulePath, "../../"));
            // gets the ThirdParty folder directory path
            string ConnectorPath = ThirdPartyPath;

            //string[] strExternalLibPath = { "libminizip", "libjsoncpp", "libzlib", "libcurl", "libanl", "libprotobuf", "libcryptopp" };
            //string[] strExternalLibName = { "static_minizip.lib", "static_jsoncpp.lib", "static_zlib.lib", "static_curl.lib", "static_anl.lib", "static_protobuf.lib", "static_cryptopp.lib" };

            //for (int i = 0; i < strExternalLibPath.Length; i++)
            //{
            //    string ConnectorLibraryPath = ConnectorPath + "x64/RelWithDebInfo";
            //    // gets the path of the lib folder      
            //    string ConnectorIncludePath = ConnectorPath + "external/" + strExternalLibPath[i] + "/source/";
            //    // gets the path of the include folder      
            //    string ConnectorImportLibraryName = Path.Combine(ConnectorLibraryPath, strExternalLibName[i]);

            //    // gets the file path and name of the libmysql.lib static import library 

            //    if (!File.Exists(ConnectorImportLibraryName))
            //    // check to ensure the static import lib can be located, or else we'll be in trouble        
            //    {
            //        throw new BuildException(string.Format("{0} could not be found.", ConnectorImportLibraryName));
            //        // log an error message explaining what went wrong if not found       
            //    }

            //    PrivateIncludePaths.Add(ConnectorIncludePath);
            //    // add the "include" folder to our dependencies. I've chosen PrivateIncludePaths since I hide the mysql headers from external code 
            //    //PublicAdditionalLibraries.Add(ConnectorLibraryPath);
            //    // add the "lib" folder to our dependencies        
            //    //PublicAdditionalLibraries.Add(ConnectorImportLibraryName);
            //    // add libmysql.lib static import library as a dependency      
            //}

            //string[] strBzbeeLibPath = { "libbaseutil", "libnetwork", "libframework" };
            //string[] strBzbeeLibName = { "static_baseutil.lib", "static_network.lib", "static_framework.lib" };

            //for (int i = 0; i < strBzbeeLibPath.Length; i++)
            //{
            //    string ConnectorLibraryPath = ConnectorPath + "x64/RelWithDebInfo";
            //    // gets the path of the lib folder      
            //    string ConnectorIncludePath = ConnectorPath + "bzbee/" + strBzbeeLibPath[i] + "/source/";
            //    // gets the path of the include folder      
            //    string ConnectorImportLibraryName = Path.Combine(ConnectorLibraryPath, strBzbeeLibName[i]);

            //    // gets the file path and name of the libmysql.lib static import library 

            //    if (!File.Exists(ConnectorImportLibraryName))
            //    // check to ensure the static import lib can be located, or else we'll be in trouble        
            //    {
            //        throw new BuildException(string.Format("{0} could not be found.", ConnectorImportLibraryName));
            //        // log an error message explaining what went wrong if not found       
            //    }

            //    PrivateIncludePaths.Add(ConnectorIncludePath);
            //    // add the "include" folder to our dependencies. I've chosen PrivateIncludePaths since I hide the mysql headers from external code 
            //    //PublicAdditionalLibraries.Add(ConnectorLibraryPath);
            //    // add the "lib" folder to our dependencies        
            //    //PublicAdditionalLibraries.Add(ConnectorImportLibraryName);
            //    // add libmysql.lib static import library as a dependency      
            //}




            {
                string strLibPath = "static_data";// { , "static_msg" };
                string strLibName = "static_data.lib";// { , "static_msg.lib" };
                string ConnectorLibraryPath = ConnectorPath + "x64/Release";
                // gets the path of the lib folder      
                string ConnectorIncludePath = ConnectorPath + "static/" + strLibPath;
                // gets the path of the include folder      
                string ConnectorImportLibraryName = Path.Combine(ConnectorLibraryPath, strLibName);

                // gets the file path and name of the libmysql.lib static import library 

                if (!File.Exists(ConnectorImportLibraryName))
                // check to ensure the static import lib can be located, or else we'll be in trouble        
                {
                    throw new BuildException(string.Format("{0} could not be found.", ConnectorImportLibraryName));
                    // log an error message explaining what went wrong if not found       
                }

                PrivateIncludePaths.Add(ConnectorIncludePath);    
            }


            {
                string strLibPath = "static_msg";// { , "static_msg" };
                string strLibName = "static_msg.lib";// { , "static_msg.lib" };
                string ConnectorLibraryPath = ConnectorPath + "x64/Release";
                // gets the path of the lib folder      
                string ConnectorIncludePath = ConnectorPath + "static/" + strLibPath;
                // gets the path of the include folder      
                string ConnectorImportLibraryName = Path.Combine(ConnectorLibraryPath, strLibName);

                // gets the file path and name of the libmysql.lib static import library 

                if (!File.Exists(ConnectorImportLibraryName))
                // check to ensure the static import lib can be located, or else we'll be in trouble        
                {
                    throw new BuildException(string.Format("{0} could not be found.", ConnectorImportLibraryName));
                    // log an error message explaining what went wrong if not found       
                }

                PrivateIncludePaths.Add(ConnectorIncludePath);   
            }

            {
                string strLibPath = "static_logic";// { , "static_msg" };
                string strLibName = "static_logic.lib";// { , "static_msg.lib" };
                string ConnectorLibraryPath = ConnectorPath + "x64/Release";
                // gets the path of the lib folder      
                string ConnectorIncludePath = ConnectorPath + "static/" + strLibPath;
                // gets the path of the include folder      
                string ConnectorImportLibraryName = Path.Combine(ConnectorLibraryPath, strLibName);

                // gets the file path and name of the libmysql.lib static import library 

                if (!File.Exists(ConnectorImportLibraryName))
                // check to ensure the static import lib can be located, or else we'll be in trouble        
                {
                    throw new BuildException(string.Format("{0} could not be found.", ConnectorImportLibraryName));
                    // log an error message explaining what went wrong if not found       
                }

                PrivateIncludePaths.Add(ConnectorIncludePath);    
            }

            //{
            //    string ConnectorIncludePath = ConnectorPath + "Source/ReichThree";
            //    PrivateIncludePaths.Add(ConnectorIncludePath);

            //    string ConnectorIncludePath1 = ConnectorPath + "Source";
            //    PrivateIncludePaths.Add(ConnectorIncludePath1);
            //}


            //PrivateIncludePathModuleNames.Add("WebBrowser");
        }
    }
}
