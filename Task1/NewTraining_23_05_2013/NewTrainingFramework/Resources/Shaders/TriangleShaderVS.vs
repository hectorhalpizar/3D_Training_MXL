attribute vec3 a_posL;
attribute vec4 a_colorL;
varying vec4 v_color;
void main()
{
vec4 posL = vec4(a_posL, 1.0);
vec4 colorL = a_colorL;
gl_Position = posL;
v_color = colorL;
}
   