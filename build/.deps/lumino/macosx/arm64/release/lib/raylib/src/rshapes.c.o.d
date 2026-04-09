{
    depfiles = "build/.objs/lumino/macosx/arm64/release/lib/raylib/src/__cpp_rshapes.c.c:   lib/raylib/src/rshapes.c lib/raylib/src/raylib.h   lib/raylib/src/config.h lib/raylib/src/rlgl.h\
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
        "lib/raylib/src/rshapes.c"
    },
    depfiles_format = "gcc"
}