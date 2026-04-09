{
    depfiles = "build/.objs/lumino/macosx/arm64/release/lib/raylib/src/__cpp_rmodels.c.c:   lib/raylib/src/rmodels.c lib/raylib/src/raylib.h   lib/raylib/src/config.h lib/raylib/src/rlgl.h lib/raylib/src/raymath.h   lib/raylib/src/external/tinyobj_loader_c.h   lib/raylib/src/external/cgltf.h lib/raylib/src/external/vox_loader.h   lib/raylib/src/external/m3d.h lib/raylib/src/external/par_shapes.h\
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
        "lib/raylib/src/rmodels.c"
    },
    depfiles_format = "gcc"
}