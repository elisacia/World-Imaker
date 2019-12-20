#version 330 core


layout(location = 0) in vec3 aVertexPosition; 
layout(location = 1) in vec3 aVertexNormal;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vPosition_vs; 
out vec3 vNormal_vs;
out int vCubeType;

void main() {
    // Passage en coordonnées homogènes
    vec4 vertexPosition = vec4(aVertexPosition, 1);
    vec4 vertexNormal = vec4(aVertexNormal, 0);

    // Calcul des valeurs de sortie
    vPosition_vs = vec3(uMVMatrix * vertexPosition);
    vNormal_vs = vec3(vertexNormal);

    // Calcul de la position projetée
    gl_Position = uMVPMatrix * vertexPosition;
}