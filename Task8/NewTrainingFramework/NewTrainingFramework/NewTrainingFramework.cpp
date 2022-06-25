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
#include "Fog.h"

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
	Fog::DestroyInstance();
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
