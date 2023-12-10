#version 330
layout(location=0) in vec3 in_position;
layout(location=1) in vec3 in_normal;
layout(location=2) in vec2 in_uv;
//layout(location=3) in vec3 in_tangent;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragPos;
out vec3 normal;
out vec2 uv;

void main () {
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(in_position, 1);

    fragPos = vec3(modelMatrix * vec4(in_position, 1));

    normal = in_normal;
    normal = transpose(inverse(mat3(modelMatrix))) * in_normal;
//    normal = mat3(transpose(inverse(modelMatrix))) * in_normal;

    uv = in_uv;
}