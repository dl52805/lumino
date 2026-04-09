{
    depfiles = "build/.objs/lumino/macosx/arm64/release/lib/raylib/src/__cpp_rtextures.c.c:   lib/raylib/src/rtextures.c lib/raylib/src/raylib.h   lib/raylib/src/config.h lib/raylib/src/rlgl.h   lib/raylib/src/external/stb_image.h lib/raylib/src/external/rltexgpu.h   lib/raylib/src/external/qoi.h   lib/raylib/src/external/stb_image_write.h   lib/raylib/src/external/stb_perlin.h   lib/raylib/src/external/stb_image_resize2.h\
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
        "lib/raylib/src/rtextures.c"
    },
    depfiles_format = "gcc"
}