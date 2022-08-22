#version 460 core

layout (location = 0) out vec4 color;

layout (location = 0) in vec3 outPosition;

void main() {
    color = vec4(outPosition, 1.0);
}
