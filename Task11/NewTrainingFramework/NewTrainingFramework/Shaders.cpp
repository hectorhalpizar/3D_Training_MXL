#include "stdafx.h"
#include "Shaders.h"
#include "Log.h"

#define TAG "SHADER"

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	error = 0;
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);
	
	if (getID() == 6)
		Log::GetInstance()->printMessage(TAG, "BREAK POINT!");

	if ( vertexShader == 0 )
	{
		error = -1;
		return error;
	}
	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		error = -2;
		return error;
	}
	
	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	colorAttribute = glGetAttribLocation(program, "a_colorL");
	a_uv = glGetAttribLocation(program, "a_uv");
	normalAttribute = glGetAttribLocation(program, "a_normL");

	worldMatrixLoc = glGetUniformLocation(program, "u_worldMatrix");

	worldViewProjection = glGetUniformLocation(program, "u_WVP");
	uniformLocation = glGetUniformLocation(program, "u_s_texture");

	uniformTileFactor = glGetUniformLocation(program, "u_tileFactor");	

	uniformLocation0 = glGetUniformLocation(program, "u_s_texture0");
	uniformLocation1 = glGetUniformLocation(program, "u_s_texture1");
	uniformLocation2 = glGetUniformLocation(program, "u_s_texture2");
	uniformBlendMap = glGetUniformLocation(program, "u_s_blend_map");

	//fog
	uniformWorldCoord = glGetUniformLocation(program, "u_posCamera");	

	uniformFogColor = glGetUniformLocation(program, "u_fogColor");
	uniformFogStart = glGetUniformLocation(program, "u_fogStart");
	uniformFogRange = glGetUniformLocation(program, "u_fogRange");

	uniformTime = glGetUniformLocation(program, "u_Time");
	uniformDispTex = glGetUniformLocation(program, "Displ_tex");
	uniformFireTex = glGetUniformLocation(program, "FireTexture");
	uniformFireMask = glGetUniformLocation(program, "FireMask");

	//Lights
	uniformAmbColor = glGetUniformLocation(program, "u_ambient_color");
	uniformAmbWeight = glGetUniformLocation(program, "u_ambient_weight");
	uniformSpecularPower = glGetUniformLocation(program, "u_specular_power");

	uniformNumLights = glGetUniformLocation(program, "u_numLights");
	uniformLightType = glGetUniformLocation(program, "u_light_type");
	uniformPosDir = glGetUniformLocation(program, "u_pos_dir");
	uniformLightColor = glGetUniformLocation(program, "u_color");

	//NormalMap
	tangentAttribute = glGetAttribLocation(program, "a_tgtL");
	binormalAttribute = glGetAttribLocation(program, "a_binormalL");

	return error;
}

void Shaders::setID(unsigned int id)
{
	m_ID = id;
}

unsigned int Shaders::getID()
{
	return m_ID;
}

int Shaders::getError()
{
	return error;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}