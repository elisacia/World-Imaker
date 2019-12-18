#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;

uniform int uCubeType;
 
out vec3 fFragColor;

void main() {
if(uCubeType == 1) fFragColor = vec3(1.0f,0.3f,0.2f); //red
if(uCubeType == 2) fFragColor = vec3(1.0f,1.0f,1.0f); //white
if(uCubeType == 3) fFragColor = vec3(1.0f,0.7f,0.1f); //yellow
}
