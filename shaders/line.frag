#version 450

out vec4 color;

uniform vec3 col;

void main() {

    color = vec4(col, 1.0);

}
