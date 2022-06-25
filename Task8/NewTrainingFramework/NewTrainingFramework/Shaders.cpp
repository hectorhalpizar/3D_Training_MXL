#include <stdafx.h>
#include "Shaders.h"
#include "Log.h"

#define TAG "SHADER"

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	error = 0;
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

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

	Log::GetInstance()->printMessage(TAG, "Vertex shader file [%s]", fileVertexShader);
	Log::GetInstance()->printMessage(TAG, "Fragment shader file [%s]", fileFragmentShader);
	Log::GetInstance()->printMessage(TAG, "program [%d]", program);
	Log::GetInstance()->printMessage(TAG, "positionAttribute [%d]", positionAttribute);
	Log::GetInstance()->printMessage(TAG, "colorAttribute [%d]", colorAttribute);
	Log::GetInstance()->printMessage(TAG, "a_uv [%d]", a_uv);
	Log::GetInstance()->printMessage(TAG, "a_uv [%d]", a_uv);
	Log::GetInstance()->printMessage(TAG, "worldViewProjection [%d]", worldViewProjection);
	Log::GetInstance()->printMessage(TAG, "uniformlocation [%d]", uniformLocation);
	Log::GetInstance()->printMessage(TAG, "uniformlocation0 [%d]", uniformLocation0);
	Log::GetInstance()->printMessage(TAG, "uniformlocation1 [%d]", uniformLocation1);
	Log::GetInstance()->printMessage(TAG, "uniformlocation2 [%d]", uniformLocation2);
	Log::GetInstance()->printMessage(TAG, "uniformBlendMap [%d]", uniformBlendMap);
	Log::GetInstance()->printMessage(TAG, "uniformTileFactor [%d]", uniformTileFactor);
	Log::GetInstance()->printMessage(TAG, "worldCoord [%d]", uniformWorldCoord);
	Log::GetInstance()->printMessage(TAG, "uniformFogColor [%d]", uniformFogColor);
	Log::GetInstance()->printMessage(TAG, "uniformFogStart [%d]", uniformFogStart);
	Log::GetInstance()->printMessage(TAG, "uniformFogRange [%d]", uniformFogRange);

	//uniformFogColor = glGetUniformLocation(program, "u_fogColor");
	//uniformFogStart = glGetUniformLocation(program, "u_fogStart");
	//uniformFogRange = glGetUniformLocation(program, "u_fogRange");

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