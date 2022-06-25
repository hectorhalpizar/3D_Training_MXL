precision mediump float;
varying vec4 v_color;
varying vec2 v_uv;
varying vec2 v_uvTiling;

uniform sampler2D u_s_texture0;
uniform sampler2D u_s_texture1;
uniform sampler2D u_s_texture2;

uniform sampler2D u_s_blend_map;

//fog
uniform vec3 u_posCamera;
varying vec4 v_worldCoor;

uniform vec4 u_fogColor;
uniform float u_fogStart;
uniform float u_fogRange;


void main()
{
	vec4 grass = texture2D(u_s_texture0, v_uvTiling);
	vec4 dirt = texture2D(u_s_texture1, v_uvTiling);
	vec4 rock = texture2D(u_s_texture2, v_uvTiling);
	vec4 blend = texture2D(u_s_blend_map, v_uv);
	
	vec4 terrainColor = (rock*blend.x + grass*blend.y + dirt*blend.z) / (blend.x+blend.y+blend.z);
	vec4 posCamera = vec4(u_posCamera, 1.0);
	//float distanceCamera = distance(u_posCamera, v_worldCoor.xyz);		
	float distanceCamera = distance(posCamera, v_worldCoor);	
	float factor = (distanceCamera - u_fogStart) / u_fogRange;
	factor = clamp(factor, 0.0, 1.0);
	
	gl_FragColor = mix(terrainColor, u_fogColor, factor);
	//gl_FragColor = terrainColor;
}
