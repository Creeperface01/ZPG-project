//#version 330
//
//layout(location=0) in vec4 in_position;
//layout(location=1) in vec4 in_color;
//
//uniform mat4 modelMatrix;
//uniform mat4 viewMatrix;
//uniform mat4 projectionMatrix;
//
//out vec4 worldPos;
//out vec4 color;
//
//void main () {
//    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * in_position;
//    worldPos = modelMatrix * in_position;
//    color = in_color;
//}

#version 330
layout(location=0) in vec4 in_position;
layout(location=1) in vec4 in_color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main () {
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * in_position;
    color = in_color;
}