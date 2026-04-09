{
    depfiles_format = "gcc",
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
        "lib/raylib/src/rglfw.c"
    },
    depfiles = "build/.objs/lumino/macosx/arm64/release/lib/raylib/src/__cpp_rglfw.c.c:   lib/raylib/src/rglfw.c lib/raylib/src/external/glfw/src/init.c   lib/raylib/src/external/glfw/src/internal.h   lib/raylib/src/external/glfw/src/../include/GLFW/glfw3.h   lib/raylib/src/external/glfw/src/platform.h   lib/raylib/src/external/glfw/src/null_platform.h   lib/raylib/src/external/glfw/src/cocoa_platform.h   lib/raylib/src/external/glfw/src/null_joystick.h   lib/raylib/src/external/glfw/src/cocoa_joystick.h   lib/raylib/src/external/glfw/src/posix_thread.h   lib/raylib/src/external/glfw/src/cocoa_time.h   lib/raylib/src/external/glfw/src/../include/GLFW/glfw3native.h   lib/raylib/src/external/glfw/src/platform.c   lib/raylib/src/external/glfw/src/context.c   lib/raylib/src/external/glfw/src/monitor.c   lib/raylib/src/external/glfw/src/window.c   lib/raylib/src/external/glfw/src/input.c   lib/raylib/src/external/glfw/src/mappings.h   lib/raylib/src/external/glfw/src/vulkan.c   lib/raylib/src/external/glfw/src/posix_module.c   lib/raylib/src/external/glfw/src/posix_thread.c   lib/raylib/src/external/glfw/src/cocoa_init.m   lib/raylib/src/external/glfw/src/cocoa_joystick.m   lib/raylib/src/external/glfw/src/cocoa_monitor.m   lib/raylib/src/external/glfw/src/cocoa_window.m   lib/raylib/src/external/glfw/src/cocoa_time.c   lib/raylib/src/external/glfw/src/nsgl_context.m   lib/raylib/src/external/glfw/src/egl_context.c   lib/raylib/src/external/glfw/src/osmesa_context.c\
"
}