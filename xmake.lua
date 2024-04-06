set_project("pts")
set_version("0.1.0", {build = "%Y%m%d%H%M%S"})

add_languages("c++17")
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})
add_rules("mode.debug", "mode.release")
add_repositories("st_repo git@github.com:yobome/xmake-repo.git yobome/dev")


add_requires("stlog v1.0.1")
add_requires("toml++ v3.4.0")
add_requires("cmdline 2014.2.4")
add_requires("zeromq 4.3.5", {system = false, configs = {shared = true}})
add_requires("ctp v6.7.2")

target("pts")
    set_kind("binary")
    add_includedirs("include")
    add_configfiles("src/VERSION.in")
    add_files("src/*.cpp")
    add_packages(
        "stlog",
        "toml++",
        "cmdline",
        "zeromq",
        "ctp"
    )
    add_installfiles("$(buildir)/VERSION")
    add_installfiles("config_template.toml", {prefixdir = "config", filename = "config.toml"})
    add_installfiles("run.sh")
target_end()