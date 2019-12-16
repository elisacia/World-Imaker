#version 330 core

in vec3 vPosition_vs; 
in vec3 vNormal_vs;
in vec2 vTexCoords; 

uniform sampler2D uTexture;

out vec3 fFragColor;

void main() {
	vec4 color = texture(uTexture, vTexCoords);
    fFragColor = color.rgb;
}
