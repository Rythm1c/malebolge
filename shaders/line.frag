#version 450

out vec4 color;

uniform vec3 col;

void main() {

    color = vec4(col, 1.0); /*  vec4(0.19, 0.62, 0.96, 0.0); */

}
