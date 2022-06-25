precision mediump float;
varying vec2 v_uv;
uniform float u_Time;

uniform sampler2D Displ_tex;
uniform sampler2D FireTexture;
uniform sampler2D FireMask;

void main()
{	
	vec2 disp = texture2D(Displ_tex, vec2(v_uv.x, v_uv.y + u_Time)).rg;
	vec2 dMax = vec2(-0.1, 0.15); //simulate the brownian motion of the particles
	vec2 offset = (2.0 * disp - 1.0) * dMax;	
	
	vec2 Tex_coords_displaced = v_uv + offset;
	vec4 fire_color = texture2D (FireTexture, Tex_coords_displaced);
	
	vec4 AlphaValue = texture2D(FireMask, v_uv);
	gl_FragColor = fire_color * (1.0, 1.0 , 1.0, AlphaValue.r);
}