#version 330 core

in vec3 vPosition_vs; 
in vec3 vNormal_vs;
in vec2 vTexCoords; 

uniform sampler2D uTexture1;
uniform sampler2D uTexture2;


out vec3 fFragColor;

void main() {
	vec4 color1 = texture(uTexture1, vTexCoords);
	vec4 color2 = texture(uTexture2, vTexCoords);
    fFragColor = color1.rgb+color2.rgb;
}
