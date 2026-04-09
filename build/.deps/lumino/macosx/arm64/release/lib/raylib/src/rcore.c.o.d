{
    depfiles = "build/.objs/lumino/macosx/arm64/release/lib/raylib/src/__cpp_rcore.c.c:   lib/raylib/src/rcore.c lib/raylib/src/raylib.h lib/raylib/src/config.h   lib/raylib/src/rlgl.h lib/raylib/src/external/glad.h   lib/raylib/src/raymath.h lib/raylib/src/rgestures.h   lib/raylib/src/rcamera.h lib/raylib/src/external/sinfl.h   lib/raylib/src/external/sdefl.h lib/raylib/src/external/rprand.h\
",
    values = {
        "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang",
        {
            "-Qunused-arguments",
            "-target",
            "arm64-apple-macos15.7",
            "-isysroot",
            "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX26.1.sdk",
            "-fvisibility=hidden",
            "-O3",
            "-Ilib/raylib/src",
            "-DPLATFORM=PLATFORM_DESKTOP",
            "-framework",
            "Foundation",
            "-framework",
            "OpenGL",
            "-framework",
            "Cocoa",
            "-framework",
            "IOKit",
            "-framework",
            "CoreAudio",
            "-ObjC",
            "-DNDEBUG"
        }
    },
    files = {
        "lib/raylib/src/rcore.c"
    },
    depfiles_format = "gcc"
}