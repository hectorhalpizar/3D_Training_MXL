precision mediump float;
varying vec4 v_color;
varying vec2 v_uv;
varying vec2 v_uvTiling;

uniform sampler2D u_s_texture0;
uniform sampler2D u_s_texture1;
uniform sampler2D u_s_texture2;

uniform sampler2D u_s_blend_map;

void main()
{
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	//gl_FragColor = v_color;
	//gl_FragColor = texture2D(u_s_texture, v_uv);
	vec4 grass = texture2D(u_s_texture0, v_uvTiling);
	vec4 dirt = texture2D(u_s_texture1, v_uvTiling);
	vec4 rock = texture2D(u_s_texture2, v_uvTiling);
	vec4 blend_map = texture2D(u_s_blend_map, v_uv);

}
