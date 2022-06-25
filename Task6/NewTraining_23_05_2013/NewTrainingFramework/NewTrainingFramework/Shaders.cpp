#include <stdafx.h>
#include "Shaders.h"

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
	worldMatrixLoc = glGetUniformLocation(program, "u_WMatrix");
	worldViewProjection = glGetUniformLocation(program, "u_WVP");	
	uniformLocation = glGetUniformLocation(program, "u_s_texture");
	

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