#include "stdafx.h"
#include "Object.h"
#include "Log.h"
#include "SceneManager.h"

#define TAG "OBJECT"

short Object::indexTex = 0;

Object::Object()
{
	m_tex2DPtrPtr = NULL;
	m_texCubePtrPtr =  NULL;
}

void Object::set(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ)
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
}

void Object::Update()
{

}

void Object::Draw()
{
	Log::GetInstance()->printMessage(TAG, "ID [%d]", getID());

	Log::GetInstance()->printMessage(TAG, "Shader ID [%d]", m_shaderPtr->getID());
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
		glEnableVertexAttribArray(m_shaderPtr->a_uv);
		glVertexAttribPointer(m_shaderPtr->a_uv, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(16 * sizeof(float)));
	}

	//for (int i = 0; i < getCubeTexAmount(); i ++)
	//{
	//	Log::GetInstance()->printMessage(TAG, "tex2D [%d]",m_texCubePtrPtr[i]->getID());
	//}

	for (int i = 0; i < get2DTexAmount(); i ++)	
	{
		//Log::GetInstance()->printMessage(TAG, "tex2D [%d] TexIndex [%d]",m_tex2DPtrPtr[i]->getID(), Object::indexTex);
		// make active a texture unit	
		glActiveTexture(GL_TEXTURE0 + Object::indexTex); 

		// bind the texture to the currently active texture unit
		glBindTexture(GL_TEXTURE_2D, m_tex2DPtrPtr[i]->getTexHandle());	 

		// set the uniform sampler
		glUniform1i(m_shaderPtr->uniformLocation, Object::indexTex);		

		Object::indexTex ++;
	}

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_modelPtr->getm_hIndexBuffer());
	glDrawElements( GL_TRIANGLES, m_modelPtr->getIndicesNum(), GL_UNSIGNED_INT, (void*)0 );

	//Log::GetInstance()->printMessage(TAG, "Ends Object");

}

void Object::Init()
{

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