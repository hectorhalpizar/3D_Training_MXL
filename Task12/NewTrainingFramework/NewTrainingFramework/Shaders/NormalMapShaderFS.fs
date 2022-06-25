precision mediump float;

//varying vec3 v_normW;
varying vec3 v_posW;
varying vec2 v_uv;
varying vec3 v_tgtW;
varying vec3 v_binormalW;
varying mat3 TBN;

uniform vec3  u_ambient_color;
uniform float u_ambient_weight;
uniform float u_specular_power[10];

uniform int u_numLights;
uniform int	u_light_type[10];
uniform vec3 u_pos_dir[10];
uniform vec3 u_color[10];

uniform sampler2D u_s_texture0;
uniform sampler2D u_s_texture1;

vec3 getlightDirection(int i) {
	if(u_light_type[i]==0) {
		return u_pos_dir[i];
	} else {
		return normalize(v_posW - u_pos_dir[i]);
	}
}

vec3 diffuseCI(vec3 Normal, vec3 lightDirection, int i) {
	float diffuse = dot(-lightDirection, Normal);
	float diffuseintensity = max(diffuse, 0.0);
	vec3 diffuseColor = u_color[i];
	vec3 diffuseComponent = (diffuseintensity * diffuseColor);
	return diffuseComponent;
}

vec3 specularFunc(vec3 lightDirection, vec3 Normal, int i) {
	vec3 reflectDirection = normalize(reflect(lightDirection, Normal));
	float Specular = dot(reflectDirection, Normal);
	float intensity = max(Specular, 0.0);
	float SpecularIntensity = pow(intensity, u_specular_power[i]);
	vec3 SpecularColor = u_color[i];
	return SpecularColor * SpecularIntensity ;
}

void main()
{
	//vec3 Normal = normalize(v_normW);
	vec3 vecColor = texture2D(u_s_texture1, v_uv).xyz;
	vec3 Normal = normalize(TBN * (2.0 * vecColor - 1.0));
	vec3 totalDifusse = vec3(0.0,0.0,0.0);
	vec3 totalSpecular = vec3(0.0,0.0,0.0);
	vec3 lightDirection[10];
	
	for (int i = 0; i < u_numLights; i++)
	{
		lightDirection[i] = getlightDirection(i);
		totalDifusse+=diffuseCI(Normal, lightDirection[i], i);
		totalSpecular+=specularFunc(lightDirection[i], Normal, i);
	}
	
	vec4 ObjColor = texture2D(u_s_texture0, v_uv);
	float ambiet = (1.0 - u_ambient_weight);
	vec3 total = (u_ambient_color * u_ambient_weight + totalDifusse * ambiet);
	vec3 specular = (total * ObjColor.xyz + totalSpecular ).xyz;
	gl_FragColor = vec4(specular, ObjColor.w);
	
	
	// gl_FragColor = vec4(((u_ambient_color * u_ambient_weight + 
							// totalDifusse  * 
							// (1.0 - u_ambient_weight)) * ObjColor.xyz + 
							// totalSpecular ).xyz, ObjColor.w);
}