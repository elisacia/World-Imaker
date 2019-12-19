#version 330 core

in vec3 vPosition_vs; 
in vec3 vNormal_vs;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;


out vec3 fFragColor;

vec3 blinnPhong(){

  // formule=Li(Kd(wi.N)+Ks(halfVector.N)shininess)

	vec3 wi= normalize(uLightDir_vs);
	vec3 halfVector =  ((normalize(-vPosition_vs))+wi)/2;
	vec3 p1 = uKd*(dot(wi, vNormal_vs));
	vec3 p2 = uKs*pow((dot(halfVector, vNormal_vs)),uShininess);

	return uLightIntensity*(P1+P2);

}


void main() {
	
	 fFragColor = blinnPhong();
}
