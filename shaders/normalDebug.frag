#version 450

out vec4 color;
in vec3 normal;

void main() {

    color = vec4(normalize(normal), 1.0);
}