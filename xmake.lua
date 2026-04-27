add_rules(
  "plugin.compile_commands.autoupdate",
  {
    outputdir = ".",
    lsp = "clangd"
  }
)

add_rules("mode.debug", "mode.release")

set_defaultmode("debug")

add_requires("raylib", "fmt")

target("lumino")
  set_kind("binary")
  add_files("src/*.cpp")
  set_rundir("$(projectdir)")

  add_packages("raylib")
  add_packages("fmt")

  --[[
  add_includedirs("./lib/raylib/src")
  add_linkdirs("./lib/raylib/src")
  add_links("raylib")

  add_includedirs("./lib/fmtlib/include")
  add_linkdirs("./lib/fmtlib/bin")
  add_links("fmt")

  if is_os("macosx") then
    add_frameworks("Foundation", "OpenGL", "Cocoa", "IOKit", "CoreAudio")
  elseif is_os("windows") then
    add_links({
      "msvcrt",
      "OpenGL32",
      "Gdi32",
      "WinMM",
      "kernel32",
      "shell32",
      "User32"
    })
  end
  --]]

  on_run(
    function (target)
      import("core.base.process")

      local stdout = "image.ppm"
      local proc = process.openv(
        target:targetfile(),
        {}, { stdout = stdout }
      )
      if proc then
        proc:wait()
        proc:close()
      end

      os.exec("magick image.ppm image.png")
    end
  )
