#include "stdafx.h"
#include "Object.h"
#include "Log.h"
#include "SceneManager.h"
#include "Fog.h"

#define TAG "OBJECT"

short Object::indexTex = 0;

Object::Object()
{
	m_tex2DPtrPtr = NULL;
	m_texCubePtrPtr =  NULL;
}

void Object::set(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, float tileFactor)
{
	m_posX = posX;
	m_posY = posY;
	m_posZ = posZ;
	m_rotX = rotX;
	m_rotY = rotY;
	m_rotZ = rotZ;
	m_scaleX = scaleX;
	m_scaleY = scaleY;
	m_scaleZ = scaleZ;
	m_tileFactor = tileFactor;
}

Object::~Object()
{
	if (m_tex2DPtrPtr != NULL)
	{
		delete m_tex2DPtrPtr;		
		m_tex2DPtrPtr = NULL;
	}

	if (m_texCubePtrPtr != NULL)
	{
		delete m_texCubePtrPtr;
		m_texCubePtrPtr = NULL;
	}

	if (light_Type != NULL)
	{
		delete[] light_Type;
		light_Type = NULL;
	}

	if (specular_power != NULL)
	{
		delete[] specular_power;
		specular_power = NULL;
	}

	if (light_radius != NULL)
	{
		delete[] light_radius;
		light_radius = NULL;
	}

	if (light_move_type != NULL)
	{
		delete[] light_move_type;
		light_radius = NULL;
	}

	if (light_PosDir != NULL)
	{
		delete[] light_PosDir;
		light_PosDir = NULL;
	}

	if (light_Type != NULL)
	{
		delete[] light_Type;
		light_Type = NULL;
	}

	if (speed != NULL)
	{
		delete[] speed;
		speed = NULL;
	}

	if (light_Id != NULL)
	{
		delete[] light_Id;
		light_Id = NULL;
	}

	if (light_color != NULL)
	{
		delete[] light_color;
		light_color = NULL;		
	}
}

void Object::Update(float deltaTime)
{
	m_currentDeltaTime += deltaTime;

	if (m_shaderPtr->getID() == 5)
	{
		if (light_color == NULL)
		{
			Log::GetInstance()->printMessage(TAG, "Light Amount [%d]", getLightAmount());
			light_color = new Vector3[getLightAmount()];

			}
			for (int lightIndex = 0; lightIndex < getLightAmount(); lightIndex++)
			{
				light_color[lightIndex] = SceneManager::GetInstance()->getLight(light_Id[lightIndex])->color;
				Log::GetInstance()->printMessage(TAG, "Light color [%.2f, %.2f, %.2f]", light_color[lightIndex].x, light_color[lightIndex].y, light_color[lightIndex].z);
			}			
		}

		if (light_PosDir == NULL)
		{
			light_PosDir = new Vector3[getLightAmount()];
			for (int lightIndex = 0; lightIndex < getLightAmount(); lightIndex++)
			{
				light_PosDir[lightIndex] = SceneManager::GetInstance()->getLight(light_Id[lightIndex])->pos_dir;
				Log::GetInstance()->printMessage(TAG, "Light Position/Direction [%.2f, %.2f, %.2f]", light_PosDir[lightIndex].x, light_PosDir[lightIndex].y, light_PosDir[lightIndex].z);
			}
		}

		if (light_Type == NULL)
		{
			light_Type = new int[getLightAmount()];
			for (int lightIndex = 0; lightIndex < getLightAmount(); lightIndex++)
			{
				light_Type[lightIndex] = SceneManager::GetInstance()->getLight(light_Id[lightIndex])->light_type;
			}
		}	

		if (light_move_type ==  NULL)
		{
			light_move_type = new int[getLightAmount()];
			for (int lightIndex = 0; lightIndex < getLightAmount(); lightIndex++)
			{
				light_move_type[lightIndex] = SceneManager::GetInstance()->SceneManager::GetInstance()->getLight(light_Id[lightIndex])->move_type;
			}
		}

		if (light_radius == NULL)
		{
			light_radius = new float[getLightAmount()];
			for (int lightIndex = 0; lightIndex < getLightAmount(); lightIndex++)
			{
				light_radius[lightIndex] = SceneManager::GetInstance()->SceneManager::GetInstance()->getLight(light_Id[lightIndex])->radius;
			}
		}

		if (speed == NULL)
		{
			speed = new float[getLightAmount()];
			for (int lightIndex = 0; lightIndex < getLightAmount(); lightIndex++)
			{
				speed[lightIndex] = SceneManager::GetInstance()->SceneManager::GetInstance()->getLight(light_Id[lightIndex])->speed;
			}
		}

		if (specular_power == NULL)
		{
			specular_power = new float[getLightAmount()];
			for (int lightIndex = 0; lightIndex < getLightAmount(); lightIndex++)
			{
				specular_power[lightIndex] = SceneManager::GetInstance()->SceneManager::GetInstance()->getLight(light_Id[lightIndex])->specularPower;
			}
		}
	}


void Object::Draw()
{
	if (getID() == 5)
		Log::GetInstance()->printMessage(TAG, "ID [%d]", getID());
	if (m_shaderPtr->getID() == 4)
		Log::GetInstance()->printMessage(TAG, "SHADER ID [%d]", m_shaderPtr->getID());

	//Log::GetInstance()->printMessage(TAG, "Shader ID [%d]", m_shaderPtr->getID());
	if (m_shaderPtr->getError() < 0)
	{
		return;
	}
	glUseProgram(m_shaderPtr->program);

	//Log::GetInstance()->printMessage(TAG, "Model ID [%d]", m_modelPtr->getID());
	glBindBuffer(GL_ARRAY_BUFFER, m_modelPtr->getm_hVertexBuffer());	

	if(m_shaderPtr->positionAttribute != -1)
	{
		glEnableVertexAttribArray(m_shaderPtr->positionAttribute);
		glVertexAttribPointer(m_shaderPtr->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	
	if(m_shaderPtr->colorAttribute != -1)
	{
		glEnableVertexAttribArray(m_shaderPtr->colorAttribute);
		glVertexAttribPointer(m_shaderPtr->colorAttribute, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(3 * sizeof(float)));	
	}

	if(m_shaderPtr->normalAttribute != -1)
	{
		glEnableVertexAttribArray(m_shaderPtr->normalAttribute);
		glVertexAttribPointer(m_shaderPtr->normalAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(7 * sizeof(float)));	
	}

	if(m_shaderPtr->worldMatrixLoc != -1)
	{
		Matrix wMatrix = GetWorldMatrix();
		glUniformMatrix4fv(m_shaderPtr->worldMatrixLoc, 1, GL_FALSE, &wMatrix.m[0][0]);
	}

	if(m_shaderPtr->worldViewProjection != -1)
	{
		Camera * cam = SceneManager::GetInstance()->getCamera();
		Matrix wvp = GetWorldMatrix() * cam->Calculate_View_Matrix() * cam->Calculate_Projection_Matrix();
		glUniformMatrix4fv(m_shaderPtr->worldViewProjection, 1, GL_FALSE, &wvp.m[0][0]);
	}

	if(m_shaderPtr->a_uv != -1)
	{
		if (m_shaderPtr->getID() == 5)
			Log::GetInstance()->printMessage(TAG, "BREAK POINT!");
		glEnableVertexAttribArray(m_shaderPtr->a_uv);
		glVertexAttribPointer(m_shaderPtr->a_uv, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(16 * sizeof(float)));
	}

	if (m_shaderPtr->uniformTileFactor != -1)
	{
		glUniform1f(m_shaderPtr->uniformTileFactor, m_tileFactor);
	}

	if (m_shaderPtr->uniformWorldCoord != -1)
	{
		Log::GetInstance()->printMessage(TAG, "Checing ID Shader [%d]", m_shaderPtr->getID());
		Camera * cam = SceneManager::GetInstance()->getCamera();
		//glUniform4fv(m_shaderPtr->uniformWorldCoord, 1, &cam->m_positionInfo.x);	
		glUniform3fv(m_shaderPtr->uniformWorldCoord, 1, &cam->m_positionInfo.x);	
	}

	if (m_shaderPtr->uniformFogColor != -1)
	{
		//float * tmp = &getFogColor().x;
		glUniform4fv(m_shaderPtr->uniformFogColor, 1, &Fog::GetInstance()->m_color.x);
	}

	if (m_shaderPtr->uniformFogStart != -1)
	{
		glUniform1f(m_shaderPtr->uniformFogStart, Fog::GetInstance()->m_start);
	}

	if (m_shaderPtr->uniformFogRange != -1)
	{
		glUniform1f(m_shaderPtr->uniformFogRange, Fog::GetInstance()->m_range);
	}

	if (m_shaderPtr->uniformTime != -1)
	{
		glUniform1f(m_shaderPtr->uniformTime, m_currentDeltaTime);
	}

	Log::GetInstance()->printMessage(TAG, "Shader id [%d], 2D textures amount [%d] and Cube Textures [%d]", m_shaderPtr->getID(), get2DTexAmount(), getCubeTexAmount());


	if (m_shaderPtr->getID() == 5)
			Log::GetInstance()->printMessage(TAG, "BREAK POINT!");

	for (int i = 0; i < getCubeTexAmount(); i ++)
	{
		Log::GetInstance()->printMessage(TAG, "Cube texture [%d] TexHandle [%d]",m_texCubePtrPtr[i]->getID(), m_texCubePtrPtr[i]->getTexHandle());		
		glActiveTexture(GL_TEXTURE0 + i); 

		glBindTexture(GL_TEXTURE_CUBE_MAP, m_texCubePtrPtr[i]->getTexHandle());
		glUniform1i(m_shaderPtr->uniformLocation, i);
	}

	Log::GetInstance()->printMessage(TAG, "Texture amount [%d]", get2DTexAmount());

	for (int i = 0; i < get2DTexAmount(); i ++)	
	{
		Log::GetInstance()->printMessage(TAG, "Texture 2D [%d] TexHandle [%d]",m_tex2DPtrPtr[i]->getID(), m_tex2DPtrPtr[i]->getTexHandle());
		// make active a texture unit	
		glActiveTexture(GL_TEXTURE0 + i); 

		// bind the texture to the currently active texture unit
		glBindTexture(GL_TEXTURE_2D, m_tex2DPtrPtr[i]->getTexHandle());	 

		//Log::GetInstance()->printMessage(TAG, "File name loading [%d]", m_tex2DPtrPtr[i]->getTexHandle());

		// set the uniform sampler
		if (m_shaderPtr->getID() == 1)
		{
			switch(i)
			{
				case 0:
					glUniform1i(m_shaderPtr->uniformLocation0, i);
				break;
				case 1:
					glUniform1i(m_shaderPtr->uniformLocation1, i);
				break;
				case 2:
					glUniform1i(m_shaderPtr->uniformLocation2, i);
				break;
				case 3:
					glUniform1i(m_shaderPtr->uniformBlendMap, i);
				break;
			}
		}
		else if (m_shaderPtr->getID() == 4)
		{
			switch(i)
			{
				case 0:
					Log::GetInstance()->printMessage(TAG, "uniformFireTex id [%d]", m_tex2DPtrPtr[i]->getID());
					glUniform1i(m_shaderPtr->uniformFireTex, i);
				break;
				case 1:
					Log::GetInstance()->printMessage(TAG, "uniformFireMask id [%d]", m_tex2DPtrPtr[i]->getID());
					glUniform1i(m_shaderPtr->uniformFireMask, i);
				break;
				case 2:
					Log::GetInstance()->printMessage(TAG, "uniformFireMask id [%d]", m_tex2DPtrPtr[i]->getID());
					glUniform1i(m_shaderPtr->uniformDispTex, i);
				break;
			}
		}
		else
			glUniform1i(m_shaderPtr->uniformLocation, i);		

		Object::indexTex ++;
	}

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_modelPtr->getm_hIndexBuffer());
	glDrawElements( GL_TRIANGLES, m_modelPtr->getIndicesNum(), GL_UNSIGNED_INT, (void*)0 );

	//Lights Const	
	//GLint uniformAmbColor;
	//GLint uniformAmbWeight;	
	if (m_shaderPtr->getID() == 5)
		Log::GetInstance()->printMessage(TAG, "BREAK POINT!");

	if (m_shaderPtr->uniformAmbColor != -1)
	{
		//uniformAmbColor
		//glVertexAttribPointer(m_shaderPtr->uniformAmbColor, 3, GL_FLOAT, GL_FALSE, sizeof(LightConst), 0); 	
		//glUniform3fv(m_shaderPtr->uniformAmbColor, SceneManager::GetInstance()->getLightsAmount(), &SceneManager::GetInstance()->m_lightConst.ambientColor.x);
		//Log::GetInstance()->printMessage(TAG, "Amb color [%.2f %.2f %.2f]", SceneManager::GetInstance()->m_lightConst.ambientColor.x,
		//											SceneManager::GetInstance()->m_lightConst.ambientColor.y,
		//											SceneManager::GetInstance()->m_lightConst.ambientColor.z);
		glUniform3fv(m_shaderPtr->uniformAmbColor, 1, &SceneManager::GetInstance()->m_lightConst.ambientColor.x);
	}

	//uniformAmbWeight
	if (m_shaderPtr->uniformAmbWeight != -1)
	{
		//glUniform1f(m_shaderPtr->uniformAmbWeight, SceneManager::GetInstance()->m_lightConst.ambientWeight);
		glUniform1f(m_shaderPtr->uniformAmbWeight, SceneManager::GetInstance()->m_lightConst.ambientWeight);
	}

	if (m_shaderPtr->uniformNumLights != -1)
	{
		//int tmp = SceneManager::GetInstance()->getLightsAmount();
		//glUniform1i(m_shaderPtr->uniformNumLights, tmp);
		glUniform1i(m_shaderPtr->uniformNumLights, getLightAmount());
	}

	//Lights	
	//GLint uniformNumLights;
	//GLint uniformLightType;
	//GLint uniformPosDir;
	//GLint uniformLightColor;
	//for (int indexLight = 0; indexLight < SceneManager::GetInstance()->getLightsAmount(); indexLight ++)
	//for (int indexLight = 0; indexLight < getLightAmount(); indexLight ++)
	{		
		if (m_shaderPtr->uniformSpecularPower != -1)
		{
			//uniformSpecularPower
			//glUniform1fv(m_shaderPtr->uniformSpecularPower, SceneManager::GetInstance()->getLightsAmount(), &specular_power[0]);
			glEnableVertexAttribArray(m_shaderPtr->uniformSpecularPower);
			glUniform1fv(m_shaderPtr->uniformSpecularPower,  getLightAmount(), &specular_power[0]);
		}

		//if (m_shaderPtr->uniformLightType >= 0)
		if (m_shaderPtr->uniformLightType != -1)
		{
			//glUniform1iv(m_shaderPtr->uniformLightType, SceneManager::GetInstance()->getLightsAmount(), &light_Type[0]);
			glEnableVertexAttribArray(m_shaderPtr->uniformLightType);
			glUniform1iv(m_shaderPtr->uniformLightType, getLightAmount(), &light_Type[0]);
		}

	//	if (m_shaderPtr->uniformPosDir >= 0)
		if (m_shaderPtr->uniformPosDir != -1)
		{
			//glUniform3fv(m_shaderPtr->uniformPosDir, SceneManager::GetInstance()->getLightsAmount(), &light_PosDir[0].x);
			glEnableVertexAttribArray(m_shaderPtr->uniformPosDir);
			glUniform3fv(m_shaderPtr->uniformPosDir, getLightAmount(), &light_PosDir[0].x);
		}
		
	//	if (m_shaderPtr->uniformLightColor >= 0)
		if (m_shaderPtr->uniformLightColor != -1)
		{
			//glUniform3fv(m_shaderPtr->uniformLightColor, SceneManager::GetInstance()->getLightsAmount(), &light_color[0].x);
			glEnableVertexAttribArray(m_shaderPtr->uniformLightColor);
			glUniform3fv(m_shaderPtr->uniformLightColor, getLightAmount(), &light_color[0].x);
		}
	}

	//glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_modelPtr->getm_hIndexBuffer());
	//glDrawElements( GL_TRIANGLES, m_modelPtr->getIndicesNum(), GL_UNSIGNED_INT, (void*)0 );

	//Log::GetInstance()->printMessage(TAG, "Ends Object");

}

void Object::Init()
{
	m_currentDeltaTime = 0.0f;

	light_color = NULL;
	light_PosDir = NULL;
	light_Id = NULL;
	light_Type = NULL;
	light_move_type = NULL;
	light_radius = NULL;
	speed = NULL;
	specular_power = NULL;
}

void Object::set2DTexAmount(int value)
{
	m_tex2DAmount = value;
}

int Object::get2DTexAmount()
{
	return m_tex2DAmount;
}

void Object::setCubeTexAmount(int value)
{
	m_texCubeAmount = value;
}

int Object::getCubeTexAmount()
{
	return m_texCubeAmount;
}

Matrix Object::GetWorldMatrix()
{
	Matrix m_worldMatrix;
	m_position.SetIdentity();
	m_rotationX.SetIdentity();
	m_rotationY.SetIdentity();
	m_rotationZ.SetIdentity();
	m_scale.SetIdentity();
	
	m_rotationX.SetRotationX(m_rotX);
	m_rotationX.SetRotationY(m_rotY);
	m_rotationX.SetRotationZ(m_rotZ);
	m_position.SetTranslation(m_posX, m_posY, m_posZ);
	m_scale.SetScale(m_scaleX, m_scaleY, m_scaleZ);
	//worldMatrix = scaleMatrix * rotationXMatrix * rotationYMatrix * rotationZMatrix * translationMatrix;
	m_worldMatrix = m_scale * m_rotationZ * m_rotationX * m_rotationY * m_position;
	//m_worldMatrix = m_scale * m_rotationX * m_rotationY * m_rotationZ * m_position;
	//m_worldMatrix = m_position * m_rotationX * m_rotationY * m_rotationZ;
	return m_worldMatrix;
}

void Object::setID(unsigned int id)
{
	m_ID = id;
}

unsigned int Object::getID()
{
	return m_ID;
}

void Object::setFogColor(float r, float g, float b)
{
	m_fogColor = Vector3(r, g, b);
}

Vector3 Object::getFogColor()
{
	return m_fogColor;
}

void Object::setFogStart(float value)
{
	m_fogStart = value;
}

float Object::getFogStart()
{
	return m_fogStart;
}

void Object::setFogRange(float value)
{
	m_fogRange = value;
}
	
float Object::getFogRange()
{
	return m_fogRange;
}

void Object::setLightAmount(int value)
{
	m_lightsAmount = value;
}

int Object::getLightAmount()
{
	return m_lightsAmount;
}