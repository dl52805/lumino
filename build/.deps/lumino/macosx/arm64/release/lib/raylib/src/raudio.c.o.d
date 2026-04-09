{
    depfiles = "build/.objs/lumino/macosx/arm64/release/lib/raylib/src/__cpp_raudio.c.c:   lib/raylib/src/raudio.c lib/raylib/src/raylib.h   lib/raylib/src/config.h lib/raylib/src/external/miniaudio.h   lib/raylib/src/external/dr_wav.h lib/raylib/src/external/stb_vorbis.c   lib/raylib/src/external/dr_mp3.h lib/raylib/src/external/qoa.h   lib/raylib/src/external/qoaplay.c lib/raylib/src/external/jar_xm.h   lib/raylib/src/external/jar_mod.h\
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
        "lib/raylib/src/raudio.c"
    },
    depfiles_format = "gcc"
}