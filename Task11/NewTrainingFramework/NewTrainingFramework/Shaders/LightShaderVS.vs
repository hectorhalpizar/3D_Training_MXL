attribute vec3 a_posL;
attribute vec3 a_normL;
attribute vec2 a_uv;

varying vec3 v_normW;
varying vec3 v_posW;
varying vec2 v_uv;

uniform mat4 u_WVP;
uniform mat4 u_worldMatrix;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = u_WVP * posL;
	v_normW = (u_worldMatrix * vec4(a_normL, 0.0)).xyz; //Mandar la normal en world space 
	v_posW = (u_worldMatrix * vec4(a_posL, 1.0)).xyz; //Mandar la posicion del world space
	v_uv = a_uv; //Mandar a pintar la textura	
}