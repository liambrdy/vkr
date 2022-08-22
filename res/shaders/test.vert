#version 460 core

layout (location = 0) out vec3 outPosition;

void main() {
    const vec3 positions[3] = vec3[3](
        vec3(1.f,1.f, 0.0f),
        vec3(-1.f,1.f, 0.0f),
        vec3(0.f,-1.f, 0.0f)
    );

    outPosition = positions[gl_VertexIndex];
    gl_Position = vec4(outPosition, 1.0);
}
