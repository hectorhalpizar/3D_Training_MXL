attribute vec3 a_posL;
attribute vec3 a_normL;
attribute vec2 a_uv;
attribute vec3 a_tgtL;
attribute vec3 a_binormalL;

varying vec3 v_normW;
varying vec3 v_posW;
varying vec2 v_uv;
varying vec3 v_tgtW;
varying vec3 v_binormalW;
varying vec3 toEye;
varying mat3 TBN;

uniform mat4 u_WVP;
uniform mat4 u_worldMatrix;
uniform vec3 u_posCamera; // the camera position is already in world space

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = u_WVP * posL;
	v_normW = (u_worldMatrix * vec4(a_normL, 0.0)).xyz; //Mandar la normal en world space 
	v_posW = (u_worldMatrix * vec4(a_posL, 1.0)).xyz; //Mandar la posicion del world space
	v_uv = a_uv; //Mandar a pintar la textura	
	
	v_tgtW = (u_worldMatrix * vec4(a_tgtL, 0.0)).xyz;
	v_binormalW = (u_worldMatrix * vec4(a_binormalL, 0.0)).xyz;
	TBN = mat3(normalize(v_tgtW), normalize(v_binormalW),normalize(v_normW));
	
	toEye = u_posCamera - v_posW;
}