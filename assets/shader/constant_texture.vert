#version 330

layout(location=0) in vec3 in_position;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragPos;

void main () {
    mat4 view = mat4(mat3(viewMatrix));
    gl_Position = projectionMatrix * view * vec4(in_position, 1);

    fragPos = in_position;
}