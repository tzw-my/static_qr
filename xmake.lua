add_rules("mode.debug", "mode.release")

-- https://zhuanlan.zhihu.com/p/370008884
-- I don't know how system = true means not using system package
-- add_requires("libsodium", {system = false})

-- TODO: Every system has muslcc but can't use it?
-- add_requires("muslcc")
-- set_toolchains("@muslcc")

-- xmake f -p mingw --sdk=/opt/homebrew/Cellar/mingw-w64/10.0.0_4/toolchain-x86_64/ --toolchain=mingw
toolchain("mingw")
    -- add_requires("apt::mingw-w64", {alias = "x86_64-w64-mingw32-gcc"})
    set_kind("standalone")
    set_toolset("cc", "x86_64-w64-mingw32-gcc")
    set_toolset("cxx", "x86_64-w64-mingw32-g++")
    set_toolset("ld", "x86_64-w64-mingw32-ld")
    set_toolset("ar", "x86_64-w64-mingw32-ar")
    set_toolset("ex", "x86_64-w64-mingw32-ar")
    set_toolset("strip", "x86_64-w64-mingw32-strip")
    set_toolset("as", "x86_64-w64-mingw32-as")
    add_ldflags("-static", {force = true})
    -- check toolchain
    on_check(function (toolchain)
        return import("lib.detect.find_tool")("x86_64-w64-mingw32-gcc")
    end)
toolchain_end()

-- xmake f -p macosx --toolchain=macosx
toolchain("macosx")
    -- add_requires("brew::libsodium")
    set_kind("standalone", "clang")
    set_sdkdir("/usr/bin/")
    set_toolset("cc", "cc")
    set_toolset("cxx", "c++","clang++")
    set_toolset("ld", "clang")
    set_toolset("sh", "c++", "clang")
    set_toolset("ar", "ar")
    set_toolset("ex", "ex")
    set_toolset("strip", "strip")
    set_toolset("mm", "clang")
    set_toolset("mxx", "clang", "clang++")
toolchain_end()

toolchain("linux")
    -- add_requires("apt::libsodium")
    add_ldflags("-static", {force = true})
toolchain_end()


target("sodium")
    add_packages("libsodium")
    set_kind("binary")
    add_files("src/**.c")
    set_policy("build.merge_archive", true)