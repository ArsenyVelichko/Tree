#version 320 es

in vec4 position;
//TODO split to two different matrices
uniform mat4 mvpMatrix;

void main() {
    gl_Position = mvpMatrix * position;
}
