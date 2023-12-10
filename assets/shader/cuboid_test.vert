#version 330
layout(location=0) in vec3 in_position;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 color;

void main () {
     gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(in_position, 1);

     color = vec4(1, 0, 0, 1);
}