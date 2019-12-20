#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;

uniform int uCubeType;
uniform vec4 uLightDir;

//ut vec3 fFragColor;
out vec4 fFragColor;


void main() {


float luminosity=max(-dot(uLightDir.xyz,vNormal_vs),0.2);
float addLuminosity=luminosity;

if( uLightDir.w>0.5){

	vec3 direction=normalize( vPosition_vs - uLightDir.xyz );
	float luminosityPoint=max(-dot(direction,vNormal_vs),0.1);

	addLuminosity = min(luminosity+luminosityPoint, 1);
}




  // formule=Li(Kd(wi.N)+Ks(halfVector.N)shininess)

	// vec3 wi= normalize(uLightDir_vs);
	// vec3 halfVector =  ((normalize(-vPosition_vs))+wi)/2;
	// vec3 p1 = uKd*(dot(wi, vNormal_vs));
	// vec3 p2 = uKs*pow((dot(halfVector, vNormal_vs)),uShininess);


if(uCubeType == 1) fFragColor = vec4(addLuminosity*vec3(1.0f,0.08f,0.08f),1.0f); //red
if(uCubeType == 2) fFragColor = vec4(addLuminosity*vec3(0.05f,0.05f,1.0f),1.0f); //blue
if(uCubeType == 3) fFragColor = vec4(addLuminosity*vec3(1.0f,0.8f,0.08f),1.0f); //yellow


}
