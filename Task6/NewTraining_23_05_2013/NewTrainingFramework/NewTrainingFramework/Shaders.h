#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
private:
	unsigned int m_ID;
	int error;

public:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute;
	GLint colorAttribute;
	GLint worldMatrixLoc;
	GLint worldViewProjection;
	GLint uniformLocation;
	GLint a_uv;

	int Init(char * fileVertexShader, char * fileFragmentShader);
	unsigned int getID();
	void setID(unsigned int id);
	int getError();
	~Shaders();
};