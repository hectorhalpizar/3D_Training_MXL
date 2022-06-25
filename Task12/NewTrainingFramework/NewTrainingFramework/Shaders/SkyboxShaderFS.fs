precision mediump float;
varying vec3 v_posl;
uniform samplerCube u_s_texture;

void main()
{
	gl_FragColor=textureCube(u_s_texture, v_posl);
}
