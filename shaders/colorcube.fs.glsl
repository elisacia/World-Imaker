#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;

uniform int uCubeType;
uniform vec3 uLightDir;
uniform vec3 uLightPoint;

//ut vec3 fFragColor;
out vec4 fFragColor;

// vec3 blinnPhong(){

// 	//vec3 LightIntensity = vec3(uLightIntensity);
// 	vec3 Kd = vec3(4.f);
// 	vec3 Ks = vec3(3.f);
// 	float Shininess = 0.2f;

// 	vec3 wi= normalize(uLightDir);
// 	vec3 halfVector =  normalize(-vPosition_vs);
// 	vec3 P1 = Kd*(dot(wi, vNormal_vs));
// 	vec3 P2 = Ks*pow((dot(halfVector, vNormal_vs)),Shininess);
// 	//vec3 color= LightIntensity*(P1+P2);
// 	vec3 color= uLightIntensity*(P1+P2);
// 	return color;

// }

void main() {

float luminosity=max(-dot(uLightDir,vNormal_vs),0.2);
//vec3 direction=normalize(uLightPoint-vPosition_vs);
//float luminosityPoint=max(-dot(direction,vNormal_vs),0.2);
//float addLuminosity = min(luminosity+luminosityPoint, 1);
//vec3 color = vec3(0.8, 0.3, 0.1);
//fragColor = vec4(color*luminosity,1.0);


if(uCubeType == 1) fFragColor = vec4(luminosity*vec3(1.0f,0.08f,0.08f),1.0f); //red
if(uCubeType == 2) fFragColor = vec4(luminosity*vec3(0.05f,0.05f,1.0f),1.0f); //blue
if(uCubeType == 3) fFragColor = vec4(luminosity*vec3(1.0f,0.8f,0.08f),1.0f); //yellow

//fFragColor = vec4(vNormal_vs,1.);

}
