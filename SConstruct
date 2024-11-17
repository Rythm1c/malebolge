env = Environment(
    CC=["g++"],
    CCFLAGS=[
        "-std=c++17",
        "-O2",
    ],
)

env.ParseConfig("pkg-config --cflags --libs sdl2 gl glew")

env.Program(
    target="player",
    source=[
        "main.cpp",
        Glob("animation/*.cc"),
        Glob("math/*.cc"),
        Glob("src/*.cc"),
        Glob("imgui/*.cpp"),
        Glob("shapes/*.cc"),
        Glob("foreign/*.cc"),
    ],
)
