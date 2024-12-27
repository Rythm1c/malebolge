env = Environment(
    CC=["g++"],
    CCFLAGS=[
        "-std=c++17",
        "-O2",
    ],
)

# env.ParseConfig("pkg-config --cflags --libs sdl2 gl glew")

# Progress("Evaluating $TARGET\n")

env.Program(
    LIBS=[
        "SDL2",
        "GL",
        "GLEW",
    ],
    source=[
        "main.cc",
        Glob("animation/*.cc"),
        Glob("math/*.cc"),
        Glob("src/*.cc"),
        Glob("imgui/*.cpp"),
        Glob("shapes/*.cc"),
        Glob("foreign/*.cc"),
        Glob("physics/*.cc"),
    ],
    target="player",
)
