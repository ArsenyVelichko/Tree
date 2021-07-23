#version 320 es

in vec4 position;

uniform mat4 mvpMat;

void main() {
    gl_Position = mvpMat * position;
}
