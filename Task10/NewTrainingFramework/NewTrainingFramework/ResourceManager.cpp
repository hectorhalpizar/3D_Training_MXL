#include "stdafx.h"
#include "ResourceManager.h"

#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Log.h"

#define TAG	"ResourceManager"

ResourceManager * ResourceManager::ms_pInstance = NULL;

ResourceManager::~ResourceManager()
{
	if (m_modelsPtr != NULL)
	{
		delete [] m_modelsPtr;
		m_modelsPtr = NULL;
	}

	if (m_tex2DPtr != NULL)
	{
		delete [] m_tex2DPtr;
		m_tex2DPtr = NULL;
	}

	if (m_texCubePtr != NULL)
	{
		delete [] m_texCubePtr;
		m_texCubePtr = NULL;
	}

	if (m_shaderPtr != NULL)
	{
		delete [] m_shaderPtr;
		m_shaderPtr = NULL;
	}
}

void ResourceManager::Init()
{
	readFile("RM.txt");
}

Model * ResourceManager::GetModel(unsigned int byID)
{
	Model * tmpModel = NULL;
	for (int indexModel = 0; indexModel < m_modelsAmount; indexModel++)
		if (m_modelsPtr[indexModel].getID() == byID)
		{
			tmpModel = &m_modelsPtr[indexModel];
			break;
		}
	return tmpModel;
}

Texture * ResourceManager::GetTexure2D(unsigned int byID)
{
	Texture * tmpTex2D = NULL;
	for (int indexTex = 0; indexTex < m_tex2DAmount; indexTex++)
		if (m_tex2DPtr[indexTex].getID() == byID)
		{
			tmpTex2D = &m_tex2DPtr[indexTex];
			break;
		}
	return tmpTex2D;
}

Texture * ResourceManager::GetTexureCube(unsigned int byID)
{
	Texture * tmpCubeTex = NULL;
	for (int indexTex = 0; indexTex < m_texCubeAmount; indexTex)
		if (m_texCubePtr[indexTex].getID() == byID)
		{
			tmpCubeTex = &m_texCubePtr[indexTex];
			break;
		}
	return tmpCubeTex;
}

Shaders * ResourceManager::GetShaders(unsigned int byID)
{
	Shaders * tmpShader = NULL;
	for (int indexShade = 0; indexShade < m_shadersAmount; indexShade++)
		if (m_shaderPtr[indexShade].getID() == byID)
		{
			tmpShader = &m_shaderPtr[indexShade];
			break;
		}
	return tmpShader;
}

char ResourceManager::readFile(const char * filePath)
{
	FILE * pFile;
	errno_t err;

	if ((err = fopen_s(&pFile, filePath, "r")) != 0)
	{
		esLogMessage("[%s]ERROR-001\tError reading file. ERROR FOPEN_S[%d]", TAG, err);
		return 1;
	}
	else
	{
		char tmpFilePath[256], tmpMode[64];
		int tmpId;
		//Parsing Models
		if(fscanf_s(pFile, "#Models: %d\n", &m_modelsAmount) != EOF)
		{
			if (m_modelsAmount > 0)
			{
				m_modelsPtr = new Model[m_modelsAmount];
				for (int indexModels = 0; indexModels < m_modelsAmount; indexModels++)
					if (fscanf_s(pFile, "ID %d\nFILE \"%s\n", &tmpId, &tmpFilePath, 256) != EOF)
					{
						int length = strlen(tmpFilePath) - 1;
						tmpFilePath[length] = '\0';
						m_modelsPtr[indexModels].setID(tmpId);
						m_modelsPtr[indexModels].InitModel((const char *) tmpFilePath);
					}
			}
		}

		//Parsing 2D Textures
		if (fscanf_s(pFile, "#2D_Textures: %d\n", &m_tex2DAmount) != EOF)
		{
			if (m_tex2DAmount > 0)
			{
				m_tex2DPtr = new Texture[m_tex2DAmount];
				for (int indexTex = 0; indexTex < m_tex2DAmount; indexTex++)
					if (fscanf_s(pFile, "ID %d\nFILE \"%s\nMODE %s\n", &tmpId, &tmpFilePath, 256, tmpMode, 64) != EOF)
					{
						int length = strlen(tmpFilePath) - 1;
						tmpFilePath[length] = '\0';
						m_tex2DPtr[indexTex].setID(tmpId);
						m_tex2DPtr[indexTex].Init(tmpFilePath, strcmp(tmpMode, "GL_REPEAT") == 0);
					}
			}
		}

		//Parsing Cube Textures
		if (fscanf_s(pFile, "#Cube_Textures: %d\n", &m_texCubeAmount) != EOF)
		{
			if (m_texCubeAmount > 0)
			{
				m_texCubePtr = new Texture[m_texCubeAmount];
				for (int indexTex = 0; indexTex < m_texCubeAmount; indexTex++)
					if (fscanf_s(pFile, "ID %d\nFILE \"%s\n", &tmpId, &tmpFilePath, 256) != EOF)
						{
							int length = strlen(tmpFilePath) - 1;
							tmpFilePath[length] = '\0';
							m_texCubePtr[indexTex].setID(tmpId);
							m_texCubePtr[indexTex].InitCubeTexture((const char *) tmpFilePath);
						}
			}
		}

		//Parsing Shaders
		if (fscanf_s(pFile, "#Shaders: %d\n", &m_shadersAmount) != EOF)
		{
			if (m_shadersAmount > 0)
			{
				char tmpFilePath2[256], tmpState[64];
				int tmpstate;
				m_shaderPtr = new Shaders[m_shadersAmount];
				for (int indexShader = 0; indexShader < m_shadersAmount; indexShader++)
					if (fscanf_s(pFile, "ID %d\nVS \"%s\nFS \"%s\nSTATES %d\n", &tmpId, &tmpFilePath, sizeof(tmpFilePath), &tmpFilePath2, sizeof(tmpFilePath2), &tmpstate) != EOF)
					{
						int length = strlen(tmpFilePath) - 1;
						tmpFilePath[length] = '\0';
						length = strlen(tmpFilePath2) - 1;
						tmpFilePath2[length] = '\0';
						Log::GetInstance()->printMessage(TAG, "Shaders FS [%s] - VS [%s]", tmpFilePath, tmpFilePath2);
						m_shaderPtr[indexShader].setID(tmpId);
						m_shaderPtr[indexShader].Init(tmpFilePath, tmpFilePath2);						
						for (int indexState = 0; indexState < tmpstate; indexState++)
							if (fscanf_s(pFile, "%s\n", &tmpState, sizeof(tmpState)) != EOF)
							{
								Log::GetInstance()->printMessage(TAG, "STATE [%s]", tmpState);
							}

					}
			}
		}
	}

	fclose(pFile);

	return 0;
}
