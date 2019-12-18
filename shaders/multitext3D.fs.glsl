#version 330

in vec2 vVertexTextCoords;

uniform sampler2D uTexture1;
uniform sampler2D uTexture2;

out vec3 fFragColor;

void main() {
  vec3 texture_color1 = texture(uTexture1, vVertexTextCoords).xyz;
  vec3 texture_color2 = texture(uTexture2, vVertexTextCoords).xyz;
  fFragColor = texture_color1 + texture_color2;
}
