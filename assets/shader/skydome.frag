#version 330

uniform sampler2D textureUnitID;

in vec3 fragPos;
in vec2 uv;

out vec4 frag_color;

void main () {
    frag_color = texture(textureUnitID, uv);
}