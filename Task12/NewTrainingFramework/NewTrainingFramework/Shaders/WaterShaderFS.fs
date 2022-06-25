precision mediump float;

varying vec3 v_normW;
varying vec3 toEye;
varying vec2 v_uv;
varying mat3 TBN;

uniform float u_fresnelPower;
uniform float u_Time;
uniform float u_ambient_weight;
uniform float u_depthAdjust;
uniform samplerCube u_s_texture;
uniform sampler2D u_s_texture0;
uniform sampler2D u_s_texture1;
uniform vec3  u_ambient_color;
uniform vec3 u_pos_dir[1];
uniform vec3 u_color[1];

vec3 diffuseC(vec3 Normal, vec3 lightDirection, int i)
{
	float diffuse = dot(-lightDirection, Normal);
	float diffuseintensity = max(diffuse, 0.0);
	vec3 diffuseColor = u_color[i];
	return (diffuseintensity * diffuseColor);
	
}

vec4 refractionColor(vec4 bottonColor, float depthAdjust ) {
	float depthFactor = clamp((depthAdjust) * v_uv.x, 0.0, 1.0);
	return mix(bottonColor, vec4(0.5, 0.25, 0.0, 0.0), depthFactor);
	//return mix(bottonColor, vec4(u_waterColor, 0.0), depthFactor);
}

vec3 refractionIlumination()
{
	vec3 Normal = normalize(v_normW);
	vec3 totalDifusse = diffuseC(Normal, u_pos_dir[0], 0);
	float ambiet = (1.0 - u_ambient_weight);
	return (u_ambient_color * u_ambient_weight + totalDifusse * ambiet);
}

vec3 dispRefraction(float depthAdjust) {
	vec2 disp = texture2D(u_s_texture1, vec2(v_uv.x, v_uv.y + u_Time)).rg;
	float u_dMax = v_uv.x * depthAdjust;
	vec2 offsetRefraction = u_dMax * (2.0 * disp - 1.0);
	vec2 fire_uv = v_uv + offsetRefraction;
	vec4 fire_color = texture2D(u_s_texture0, fire_uv);
	fire_color = refractionColor(fire_color, u_depthAdjust);
	return (refractionIlumination() * fire_color.xyz).xyz;
}

vec4 dispReflection() {
	vec2 disp = texture2D(u_s_texture1, vec2(v_uv.x, v_uv.y + u_Time)).rg;
	vec2 dMaxReflection = vec2(-1.0, 1.0);
	vec2 offsetReflection = dMaxReflection * (2.0 * disp - 1.0);

	vec3 normal = texture2D(u_s_texture1, v_uv + offsetReflection).xyz;
	normal = normalize(TBN * (2.0 * normal - 1.0));

	vec3 reflectDir = reflect(toEye, normal);
	vec4 ObjWater = textureCube(u_s_texture, -reflectDir);

	float ambiet = (1.0 - u_ambient_weight);
	vec3 total = (u_ambient_color * u_ambient_weight + ambiet);

	vec3 specular = (total * ObjWater.xyz).xyz;

	return vec4(specular, ObjWater.w);
}

void main() {
	float fresnelTerm = pow((1.0 -abs(dot(v_normW, normalize(toEye)))), u_fresnelPower);

	vec4 reflectColor = dispReflection();
	vec4 refractionColor = vec4(dispRefraction(u_depthAdjust), 1.0);
	gl_FragColor = mix(refractionColor, reflectColor, fresnelTerm);

}