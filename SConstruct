env = Environment(
    CC=["g++"],
    CCFLAGS=[
        "-std=c++23",
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
        Glob("math/*.cc"),
        Glob("src/*.cc"),
        Glob("imgui/*.cpp"),
        Glob("shapes/*.cc"),
        Glob("physics/*.cc"),
    ],
    target="player",
)
