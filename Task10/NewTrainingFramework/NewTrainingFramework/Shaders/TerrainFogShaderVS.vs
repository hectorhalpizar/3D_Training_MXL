precision mediump float;

attribute vec3 a_posL;
attribute vec4 a_colorL;
attribute vec2 a_uv;
uniform mat4 u_worldMatrix;

varying vec2 v_uv;
varying vec2 v_uvTiling;
varying vec4 v_color;

uniform mat4 u_WVP;
uniform float u_tileFactor;

//fog
uniform mat4 u_worldCoor;
varying vec4 v_worldCoor;

void main()
{
vec4 posL = vec4(a_posL, 1.0);
vec4 colorL = a_colorL;
//gl_Position = posL;
gl_Position = u_WVP * posL;
//v_color = colorL;
v_uv = a_uv;

//terrain
v_uvTiling = v_uv * u_tileFactor;

//fog
v_worldCoor = u_worldMatrix * posL;
}