#include "stdafx.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Log.h"
#include "Object.h"
#include "Fog.h"
#include "Light.h"
#include "Globals.h"
#include "math.h"

#define TAG	"SceneManager"

SceneManager * SceneManager::ms_pInstance = NULL;

SceneManager::~SceneManager()
{
	if (m_objPtr != NULL)
	{
		delete [] m_objPtr;
		m_objPtr = NULL;
	}

	//if (m_lightPtr != NULL)
	//{
	//	delete [] m_lightPtr;
	//	m_lightPtr = NULL;
	//}

	if (m_CameraPtrObj != NULL)
	{
		delete m_CameraPtrObj;
		m_CameraPtrObj = NULL;
	}

	if (m_lights != NULL)
	{
		delete[] m_lights;
		m_lights = NULL;
	}
}

int SceneManager::readFile(const char * filePath)
{
	FILE * pFile;
	errno_t err;

	if ((err = fopen_s(&pFile, filePath, "r")) != 0)
	{		
		Log::GetInstance()->printMessage(TAG, "ERROR-001: Error reading file.");
		return 1;
	}
	else
	{
		//Parsing Objects
		Log::GetInstance()->printMessage(TAG, "Parsing Objects");
		if (fscanf_s(pFile, "#Objects: %d\n", &m_objAmount) != EOF)
		{
			if (m_objAmount > 0)
			{
				m_objPtr = new Object[m_objAmount];

				for (int indexObj = 0; indexObj < m_objAmount; indexObj ++)
				{
					//Parsing ID, Models, Num Textures
					Log::GetInstance()->printMessage(TAG, "Parsing ID, Models, Num Textures");
					unsigned int tmpId, tmpModel;
					int tmpTexAmount;
					
					if (fscanf_s(pFile, "ID %d\nMODEL %d\nNUM_TEXTURES %d\n", &tmpId, &tmpModel, &tmpTexAmount) != EOF)
					{
						m_objPtr[indexObj].Init();
						m_objPtr[indexObj].setID(tmpId);
						m_objPtr[indexObj].m_modelPtr = ResourceManager::GetInstance()->GetModel(tmpModel);
						m_objPtr[indexObj].set2DTexAmount(tmpTexAmount);
						m_objPtr[indexObj].m_tex2DPtrPtr = NULL;
						m_objPtr[indexObj].m_tex2DPtrPtr = new Texture *[tmpTexAmount];

						for (int indexTex = 0; indexTex < m_objPtr[indexObj].get2DTexAmount(); indexTex++)
						{
							//Parsing Textures
							int tmpTex;							
							if (fscanf_s(pFile, "TEXTURE %d\n", &tmpTex) != EOF)
							{
								m_objPtr[indexObj].m_tex2DPtrPtr[indexTex] = ResourceManager::GetInstance()->GetTexure2D(tmpTex);
							}
						}
					}
					//Parsing Num Cube Textures
					Log::GetInstance()->printMessage(TAG, "Parsing Num Cube Textures");
					int tmpCubeTexAmount;
					if (fscanf_s(pFile, "NUM_CUBE_TEXTURES %d\n", &tmpCubeTexAmount) != EOF)
					{
						m_objPtr[indexObj].setCubeTexAmount(tmpCubeTexAmount);

						//Lack of implementation for cube textures amount
						for (int indexCubeTex = 0; indexCubeTex < m_objPtr[indexObj].getCubeTexAmount(); indexCubeTex++)
						{
							//Parsing Cube Textures
							m_objPtr[indexObj].m_texCubePtrPtr = NULL;
							m_objPtr[indexObj].m_texCubePtrPtr = new Texture *[tmpCubeTexAmount];
							int tmpTex;							
							if (fscanf_s(pFile, "TEXTURE %d\n", &tmpTex) != EOF)
							{
								m_objPtr[indexObj].m_texCubePtrPtr[indexCubeTex] = ResourceManager::GetInstance()->GetTexureCube(tmpTex);
							}
						}
					}

					//Parsing Shaders
					unsigned int tmpShader;
					Log::GetInstance()->printMessage(TAG, "Parsing Shaders");
					if (fscanf_s(pFile, "SHADER %d\n", &tmpShader) != EOF)
					{
						//Lack of implementation for shaders
						m_objPtr[indexObj].m_shaderPtr = ResourceManager::GetInstance()->GetShaders(tmpShader);
					}

					//Parsing Light
					Log::GetInstance()->printMessage(TAG, "Parsing Light");
					int tmpLightAmount;
					if (fscanf_s(pFile, "NUM_LIGTHS %d\n", &tmpLightAmount) != EOF)
					{		
						m_objPtr[indexObj].setLightAmount(tmpLightAmount);
						
						m_objPtr[indexObj].light_Id = new int[m_objPtr[indexObj].getLightAmount()];

						for (int indexLight = 0; indexLight < m_objPtr[indexObj].getLightAmount(); indexLight++)
						{
							int tmpLight;
							if (fscanf_s(pFile, "LIGHT %d\n", &tmpLight) != EOF)
							{
								m_objPtr[indexObj].light_Id[indexLight] = tmpLight;
							}
							esLogMessage("\n");
						}
					}

					//Parsing Position, rotation, scale, tilt factor
					Log::GetInstance()->printMessage(TAG, "Parsing Position, rotation, scale, tilt factor");
					float tmpPosX, tmpPosY, tmpPosZ, tmpRotX, tmpRotY, tmpRotZ, tmpSclX, tmpSclY, tmpSclZ, tmpTileFac;
					if (fscanf_s(pFile, "POSITION %f, %f, %f\nROTATION %f, %f, %f\nSCALE %f, %f, %f\nTILING_FACTOR %f\n", 
								&tmpPosX, &tmpPosY, &tmpPosZ, &tmpRotX, &tmpRotY, &tmpRotZ, &tmpSclX, &tmpSclY, &tmpSclZ, &tmpTileFac) != EOF)
					{
						//Lack of tilt factor implementation	
						m_objPtr[indexObj].set(tmpPosX, tmpPosY, tmpPosZ, tmpRotX,tmpRotY, tmpRotZ, tmpSclX, tmpSclY, tmpSclZ, tmpTileFac);
					}
				}
			}
		}//End of object implementation

		//Pasing Lights
		Log::GetInstance()->printMessage(TAG, "Parsing Lights");
		int tmpLightsAmout;
		if (fscanf_s(pFile, "#LIGHTS: %d\n", &tmpLightsAmout) != EOF)
		{
			Log::GetInstance()->printMessage(TAG, "Parsing light feature");
			float tmpAmbColorX, tmpAmbColorY, tmpAmbColorZ, tmpAmbWeight; 
			if (fscanf_s(pFile, "AMBIENTCOLOR %f, %f, %f\nAMBIENTWEITH %f\n", &tmpAmbColorX, &tmpAmbColorY, &tmpAmbColorZ, &tmpAmbWeight) != EOF)
			{
				//Lack of implementation for Ambient color and weight
				m_lightConst.ambientColor = Vector3(tmpAmbColorX, tmpAmbColorY, tmpAmbColorZ);
				m_lightConst.ambientWeight = tmpAmbWeight;
			}
			
			Log::GetInstance()->printMessage(TAG, "Parsing light objects");
			
			setLightsAmount(tmpLightsAmout);

			m_lights = new Light[getLightsAmount()];

			for (int indexLight = 0; indexLight < getLightsAmount(); indexLight ++)
			{				
				int tmpId;
				float tmpPosDirX, tmpPosDirY, tmpPosDirZ, tmpColorX, tmpColorY, tmpColorZ, tmpRadius, tmpSpeed, tmpSpecPow;
				char tmpType[64], tmpMoving[64];
				if (fscanf_s(pFile, "ID %d\nPOS/DIR %f, %f, %f\nTYPE %s\nCOLOR %f, %f, %f\nMOVING %s\nRADIUS %f\nSPEED %f\nSPECULAR_POWER %f\n", 
									&tmpId, &tmpPosDirX, &tmpPosDirY, &tmpPosDirZ, &tmpType, sizeof(tmpType), &tmpColorX,
									&tmpColorY, &tmpColorZ, &tmpMoving, sizeof(tmpMoving), &tmpRadius, &tmpSpeed, &tmpSpecPow) != EOF)
				{
					//Lack of implementation for lights
					m_lights[indexLight].ID = tmpId;
					m_lights[indexLight].pos_dir = Vector3(tmpPosDirX, tmpPosDirY, tmpPosDirZ);
					m_lights[indexLight].color = Vector3(tmpAmbColorX, tmpColorY, tmpColorZ);
					m_lights[indexLight].light_type = strcmp(tmpType, "DIRECTION") == 0 ? Globals::TYPE_DIRECTION : Globals::TYPE_POINT;
					m_lights[indexLight].move_type = strcmp(tmpMoving, "NONE") == 0 ?  Globals::MOVING_NONE : Globals::MOVING_CIRCLE;
					m_lights[indexLight].radius = tmpRadius;
					m_lights[indexLight].speed = tmpSpeed;
					m_lights[indexLight].specularPower = tmpSpecPow;
				}
			}
		}

		//Pasing Camera
		Log::GetInstance()->printMessage(TAG, "Parsing Camera");
		float tmpNear, tmpFar, tmpFOV, tmpSpeed, tmpPosX, tmpPosY, tmpPosZ, tmpRotX, tmpRotY, tmpRotZ;
		if (fscanf_s(pFile, "#CAMERA\nNEAR %f\nFAR %f\nFOV %f\nSPEED %f\nPOSITION %f, %f, %f\nROTATION %f, %f, %f\n",
			&tmpNear, &tmpFar, &tmpFOV, &tmpSpeed, &tmpPosX, &tmpPosY, &tmpPosZ, &tmpRotX, &tmpRotY, &tmpRotZ) != EOF)
		{
			if (m_CameraPtrObj == NULL)
			{
				//m_CameraPtrObj = new Camera(tmpNear, tmpFar, tmpFOV, tmpSpeed);
				m_CameraPtrObj = new Camera();
				m_CameraPtrObj->m_positionInfo = Vector3(tmpPosX, tmpPosY, tmpPosZ);
				m_CameraPtrObj->m_rotationInfo = Vector3(tmpRotX, tmpRotY, tmpRotZ);
			}
		}
		
		//Pasing FOG
		Log::GetInstance()->printMessage(TAG, "Parsing FOG");
		float tmpFogColorR, tmpFogColorG, tmpFogColorB, tmpFogStart, tmpFogRange;
		if (fscanf_s(pFile, "#FOG\nFOG_COLOR %f, %f, %f\nFOG_START %f\nFOG_RANGE %f\n",
					&tmpFogColorR, &tmpFogColorG, &tmpFogColorB, &tmpFogStart, &tmpFogRange) != EOF)
		{
			Fog::GetInstance()->m_color = Vector3(tmpFogColorR, tmpFogColorG, tmpFogColorB);
			Fog::GetInstance()->m_start = tmpFogStart;
			Fog::GetInstance()->m_range = tmpFogRange;
		}

		fclose(pFile);
	}

	return 0;
}

void SceneManager::Init()
{
	m_objPtr = NULL;
	m_CameraPtrObj = NULL;
	readFile("SM.txt");
}

void SceneManager::Update(float deltaTime)
{
	if (m_CameraPtrObj != NULL)	
		m_CameraPtrObj->Update(deltaTime);

	for (int indexObj = 0; indexObj < m_objAmount; indexObj++)
	{
		//Log::GetInstance()->printMessage(TAG, "indexObj [%d] Object::indexTex [%d]", indexObj, Object::indexTex);
		m_objPtr[indexObj].Update(deltaTime);
		
		if (m_objPtr[indexObj].m_shaderPtr->getID() == 5 
			&& m_objPtr[indexObj].getLightAmount() == 1)
		{
			int t = m_objPtr[indexObj].light_Id[0];

			if (getLight(t)->move_type == Globals::MOVING_CIRCLE)
			{
				float x = getLight(t)->radius * cos(m_objPtr[indexObj].getCurrentDeltaTime() * getLight(t)->speed);
				float z = getLight(t)->radius * sin(m_objPtr[indexObj].getCurrentDeltaTime() * getLight(t)->speed);

				//m_objPtr[indexObj].setPosition(-getLight(t)->pos_dir.x - x,
				//								-getLight(t)->pos_dir.y,
				//								-getLight(t)->pos_dir.z - z);

				
				//getLight(t)->pos_dir.x = -m_objPtr[indexObj].getX();
				//getLight(t)->pos_dir.y = -m_objPtr[indexObj].getY();
				//getLight(t)->pos_dir.z = -m_objPtr[indexObj].getZ();

/*				getLight(t)->pos_dir.x = -getLight(t)->pos_dir.x - x;
				getLight(t)->pos_dir.y = -getLight(t)->pos_dir.y;
				getLight(t)->pos_dir.z = -getLight(t)->pos_dir.z - z;	*/				
				
				m_objPtr[indexObj].light_PosDir[0].x = getLight(t)->pos_dir.x - x;
				m_objPtr[indexObj].light_PosDir[0].y = getLight(t)->pos_dir.y;
				m_objPtr[indexObj].light_PosDir[0].z = getLight(t)->pos_dir.z - z;
			}
			else if (getLight(t)->move_type == Globals::MOVING_NONE)
			{
				//getLight(t)->pos_dir = getLight(t)->pos_dir;				
				//m_objPtr[indexObj].setPosition(getLight(t)->pos_dir.x,
				//								getLight(t)->pos_dir.y,
				//								getLight(t)->pos_dir.z);
			}

			

		}
	}
}

void SceneManager::Draw()
{
	//Log::GetInstance()->printMessage(TAG, "Draw ID init...");
	for (int indexObj = 0; indexObj < m_objAmount; indexObj++)
	{
		//Log::GetInstance()->printMessage(TAG, "indexObj [%d] Object::indexTex [%d]", indexObj, Object::indexTex);
		m_objPtr[indexObj].Draw();
	}
	//Log::GetInstance()->printMessage(TAG, "Draw ID ended...");
}

void SceneManager::setLightsAmount(int value)
{
	m_lightsAmount = value;
}

int SceneManager::getLightsAmount()
{
	return m_lightsAmount;
}

Camera * SceneManager::getCamera()
{
	return m_CameraPtrObj;
}

Light * SceneManager::getLight(int byId)
{
	Light * tmpLight = NULL;
	for (int indexLight = 0; indexLight < getLightsAmount(); indexLight++)
	{
		if (m_lights[indexLight].ID == byId)
		{
			tmpLight = &m_lights[indexLight];
			break;
		}
	}
	return tmpLight;
}