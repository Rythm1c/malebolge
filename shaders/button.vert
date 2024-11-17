#version 450

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 TextureCoords;

uniform mat4 projection;
out vec2 tCoords;

void main() {
    tCoords = TextureCoords;
    gl_Position = projection * vec4(pos, 1.0, 1.0);
}