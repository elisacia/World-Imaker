#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;

uniform int uCubeType;
 
out vec3 fFragColor;

void main() {
if(uCubeType == 1) fFragColor = vec3(218.0f/255.0f,191.0f/255.0f,222.0f/255.0f);
if(uCubeType == 2) fFragColor = vec3(1.0f,220.0f/255.0f,244.0f/255.0f);
if(uCubeType == 3) fFragColor = vec3(220.0f/255.0f,1.0f,251.0f/255.0f);
}
