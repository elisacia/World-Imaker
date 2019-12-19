#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;

uniform int uCubeType;
uniform vec3 uLightDir;

//ut vec3 fFragColor;
out vec4 fFragColor;

vec3 blinnPhong(){

	vec3 LightIntensity = vec3(0.4f);
	vec3 Kd = vec3(4.f);
	vec3 Ks = vec3(3.f);
	float Shininess = 0.2f;

	vec3 wi= normalize(uLightDir);
	vec3 halfVector =  normalize(-vPosition_vs);
	vec3 P1 = Kd*(dot(wi, vNormal_vs));
	vec3 P2 = Ks*pow((dot(halfVector, vNormal_vs)),Shininess);
	vec3 color= LightIntensity*(P1+P2);
	return color;

}

void main() {
if(uCubeType == 1) fFragColor = vec4(blinnPhong()*vec3(1.0f,0.08f,0.08f),1.0f); //red
if(uCubeType == 2) fFragColor = vec4(blinnPhong()*vec3(0.05f,0.05f,1.0f),1.0f); //blue
if(uCubeType == 3) fFragColor = vec4(blinnPhong()*vec3(1.0f,0.8f,0.08f),1.0f); //yellow



}
