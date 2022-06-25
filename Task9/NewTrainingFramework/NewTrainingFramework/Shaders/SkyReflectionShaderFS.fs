precision mediump float;
uniform samplerCube u_s_texture;
uniform vec3 u_posCamera; // the camera position is already in world space
varying vec3 v_posW;
varying vec3 v_normW;
void main()
{
    vec3 toEye = u_posCamera - v_posW;
    vec3 reflectDir = reflect(normalize(-toEye), normalize(v_normW));  // reflect() in non linear
    gl_FragColor = textureCube(u_s_texture,reflectDir);
	//gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
}