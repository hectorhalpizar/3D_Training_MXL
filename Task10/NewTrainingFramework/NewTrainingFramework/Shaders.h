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
	GLint uniformLocation0;
	GLint uniformLocation1;
	GLint uniformLocation2;
	GLint uniformBlendMap;
	GLint a_uv;
	GLint uniformTileFactor;
	GLint uniformWorldCoord;
	GLint uniformFogColor;
	GLint uniformFogStart;
	GLint uniformFogRange;
	GLint normalAttribute;
	GLint uniformTime;
	GLint uniformDispTex;
	GLint uniformFireTex;
	GLint uniformFireMask;

	//Lights
	GLint uniformAmbColor;
	GLint uniformAmbWeight;
	GLint uniformSpecularPower;

	GLint uniformNumLights;
	GLint uniformLightType;
	GLint uniformPosDir;
	GLint uniformLightColor;

	int Init(char * fileVertexShader, char * fileFragmentShader);
	unsigned int getID();
	void setID(unsigned int id);
	int getError();
	~Shaders();
};