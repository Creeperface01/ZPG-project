#version 330

layout(location=0) in vec3 in_position;
layout(location=1) in vec3 in_normal;
layout(location=2) in vec2 in_uv;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragPos;
out vec3 normal;
out vec2 uv;

void main () {
    mat4 view = mat4(mat3(viewMatrix));
    gl_Position = projectionMatrix * view * vec4(in_position, 1);

    fragPos = in_position;
    normal = in_normal;
    uv = in_uv;
}