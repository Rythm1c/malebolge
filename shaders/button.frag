#version 450

uniform sampler2D s;
in vec2 tCoords;

out vec4 color;

void main() {
    vec4 texture = texture(s, tCoords);

    color = texture;
}
