#version 330

uniform samplerCube textureCube;

in vec3 fragPos;

out vec4 frag_colour;

void main () {
    frag_colour = texture(textureCube, fragPos);
}