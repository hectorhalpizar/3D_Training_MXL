// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include "Camera.h"
#include <conio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "KeyboardHandler.h"
#include "Model.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Log.h"

//GLuint vboId;
//Shaders myShaders;
//float angle;
Matrix Projection;
//int keyPressed;

//Camera * cam;
//Model * model_load;
//Texture * texture;


int Init ( ESContext *esContext )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
	glEnable(GL_DEPTH_TEST);

	ResourceManager::GetInstance()->Init();
	SceneManager::GetInstance()->Init();
	//triangle data (heap)
	//Vertex verticesData[3];

	//verticesData[0].pos.x =  0.0f;  verticesData[0].pos.y =  0.5f;  verticesData[0].pos.z =  0.0f;
	//verticesData[1].pos.x = -0.5f;  verticesData[1].pos.y = -0.5f;  verticesData[1].pos.z =  0.0f;
	//verticesData[2].pos.x =  0.5f;  verticesData[2].pos.y = -0.5f;  verticesData[2].pos.z =  0.0f;

	//verticesData[0].color.x = 1.0; verticesData[0].color.y = 0.0; verticesData[0].color.z = 0.0; verticesData[0].color.w = 1.0;
	//verticesData[1].color.x = 0.0; verticesData[1].color.y = 1.0; verticesData[1].color.z = 0.0; verticesData[1].color.w = 1.0;
	//verticesData[2].color.x = 0.0; verticesData[2].color.y = 0.0; verticesData[2].color.z = 1.0; verticesData[2].color.w = 1.0;

	//model_load = new Model();
	//model_load->InitModel("Models/Woman1.nfg");
	//buffer object
	//glGenBuffers(1, &vboId);
	//glBindBuffer(GL_ARRAY_BUFFER, vboId);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Objeto de la camara inicializada
	//cam = new Camera();
	//
	//texture = new Texture(myShaders.program);
	//texture->Init("Textures/Woman1.tga", true);
	
	//creation of shaders and program
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	return 0;

}

Matrix WorldMatrixCalc ()
{
	Matrix scaleMatrix;
	Matrix rotationXMatrix;
	Matrix rotationYMatrix;
	Matrix rotationZMatrix;
	Matrix translationMatrix;
	Matrix rotationMatrix;


	Matrix worldMatrix;
	scaleMatrix.SetIdentity();
	rotationXMatrix.SetIdentity();
	rotationYMatrix.SetIdentity();
	rotationZMatrix.SetIdentity();
	translationMatrix.SetIdentity();
	rotationMatrix.SetIdentity();	
	//rotationXMatrix.SetRotationX(angle);
	scaleMatrix.SetScale(0.8f);

	worldMatrix = scaleMatrix * rotationXMatrix * rotationYMatrix * rotationZMatrix * translationMatrix;

	return worldMatrix;
}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT);

	SceneManager::GetInstance()->Draw();

	//glUseProgram(myShaders.program);

	//glBindBuffer(GL_ARRAY_BUFFER, vboId);
	//glBindBuffer(GL_ARRAY_BUFFER, model_load->getm_hVertexBuffer());

	
	//if(myShaders.positionAttribute != -1)
	//{
	//	glEnableVertexAttribArray(myShaders.positionAttribute);
	//	glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	//}

	//
	//if(myShaders.colorAttribute != -1)
	//{
	//	glEnableVertexAttribArray(myShaders.colorAttribute);
	//	glVertexAttribPointer(myShaders.colorAttribute, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(3 * sizeof(float)));	
	//}

	//if(myShaders.worldMatrixLoc != -1)
	//{
	//	Matrix wMatrix = WorldMatrixCalc();
	//	glUniformMatrix4fv(myShaders.worldMatrixLoc, 1, GL_FALSE, &wMatrix.m[0][0]);
	//}

	//if(myShaders.worldViewProjection != -1)
	//{
	//	Matrix wvp =WorldMatrixCalc() * cam->Calculate_View_Matrix() * cam->Calculate_Projection_Matrix();
	//	glUniformMatrix4fv(myShaders.worldViewProjection, 1, GL_FALSE, &wvp.m[0][0]);
	//}

	//if(myShaders.a_uv != -1)
	//{
	//	glEnableVertexAttribArray(myShaders.a_uv);
	//	//glUniformMatrix4fv(myShaders.worldViewProjection, 2, GL_FALSE, (void *)(12 * sizeof(float)));
	//	glVertexAttribPointer(myShaders.a_uv, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(16 * sizeof(float)));
	//}

	////glDrawArrays(GL_TRIANGLES, 0, 3);
	//unsigned short textureUnit = 0;
	//// make active a texture unit	
	//glActiveTexture(GL_TEXTURE0 + textureUnit); 

	//// bind the texture to the currently active texture unit
	//glBindTexture(GL_TEXTURE_2D, texture->getTexHandle());	 

	//// set the uniform sampler
	//glUniform1i(myShaders.uniformLocation, textureUnit);
	//textureUnit++;

	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//
	//glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, model_load->getm_hIndexBuffer());
	//glDrawElements( GL_TRIANGLES, model_load->getIndicesNum(), GL_UNSIGNED_INT, (void*)0 );
	
	
	//unsigned short textureUnit = 0;
	//// make active a texture unit	
	//glActiveTexture(GL_TEXTURE0 + textureUnit); 

	//// bind the texture to the currently active texture unit
	//glBindTexture(GL_TEXTURE_2D, texture->getTexHandle());	 

	//// set the uniform sampler
	//glUniform1i(myShaders.uniformLocation, textureUnit);
	//textureUnit++;
	
	Object::indexTex = 0;

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	//cam->Update(deltaTime);
	SceneManager::GetInstance()->Update(deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{	
	KeyboardHandler::GetInstance()->check(key, bIsPressed);
}

void CleanUp()
{
	ResourceManager::DestroyInstance();
	SceneManager::DestroyInstance();
	KeyboardHandler::DestroyInstance();
	Log::DestroyInstance();
	//glDeleteBuffers(1, &vboId);
	//if (cam != NULL)
	//{
	//	delete cam;
	//	cam = NULL;
	//}

	//if (model_load != NULL)
	//{
	//	delete model_load;
	//	model_load = NULL;
	//}
	//
	//if (texture != NULL)
	//{
	//	delete texture;
	//	texture = NULL;
	//}
}

int _tmain(int argc, _TCHAR* argv[])
{
#if 0
	//Model * my_model = new Model();
	//my_model->InitModel("Models/Woman1.nfg");
	//delete my_model;
	ResourceManager::GetInstance()->readFile("RM.txt");
	SceneManager::GetInstance()->readFile("SM.txt");
	//int a = 4;
	//float b = 3.14259f;
	Log::GetInstance()->printMessage("TEST_LOG", "It's all over...");
#else
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
#endif
	_getch();

	return 0;
}
