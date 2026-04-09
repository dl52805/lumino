add_rules(
  "plugin.compile_commands.autoupdate",
  {
    outputdir = ".",
    lsp = "clangd"
  }
)

add_rules("mode.debug", "mode.release")

target("lumino")
  set_kind("binary")
  add_files("src/*.cpp")

  add_includedirs("./lib/raylib/src")
  add_linkdirs("./lib/raylib/src")
  add_links("raylib")

  if is_os("macosx") then
    add_frameworks("Foundation", "OpenGL", "Cocoa", "IOKit", "CoreAudio")
  end

