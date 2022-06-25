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
#include "Globals.h"
#include "Model.h"
#include "Texture.h"

GLuint vboId;
Shaders myShaders;
float angle;
Camera * cam;
Matrix Projection;
int keyPressed;
Model * model_load;
Texture * texture;

int Init ( ESContext *esContext )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
	glEnable(GL_DEPTH_TEST);

	//triangle data (heap)
	Vertex verticesData[3];

	verticesData[0].pos.x =  0.0f;  verticesData[0].pos.y =  0.5f;  verticesData[0].pos.z =  0.0f;
	verticesData[1].pos.x = -0.5f;  verticesData[1].pos.y = -0.5f;  verticesData[1].pos.z =  0.0f;
	verticesData[2].pos.x =  0.5f;  verticesData[2].pos.y = -0.5f;  verticesData[2].pos.z =  0.0f;

	verticesData[0].color.x = 1.0; verticesData[0].color.y = 0.0; verticesData[0].color.z = 0.0; verticesData[0].color.w = 1.0;
	verticesData[1].color.x = 0.0; verticesData[1].color.y = 1.0; verticesData[1].color.z = 0.0; verticesData[1].color.w = 1.0;
	verticesData[2].color.x = 0.0; verticesData[2].color.y = 0.0; verticesData[2].color.z = 1.0; verticesData[2].color.w = 1.0;

	model_load = new Model();
	model_load->InitModel("Models/Woman1.nfg");
	//buffer object
	//glGenBuffers(1, &vboId);
	//glBindBuffer(GL_ARRAY_BUFFER, vboId);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Objeto de la camara inicializada
	cam = new Camera();
	
	texture = new Texture(myShaders.program);
	texture->Init("Textures/Woman1.tga", true);
	
	//creation of shaders and program
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

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

	glUseProgram(myShaders.program);

	//glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ARRAY_BUFFER, model_load->getm_hVertexBuffer());

	
	if(myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	
	if(myShaders.colorAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.colorAttribute);
		glVertexAttribPointer(myShaders.colorAttribute, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(3 * sizeof(float)));	
	}

	if(myShaders.worldMatrixLoc != -1)
	{
		Matrix wMatrix = WorldMatrixCalc();
		glUniformMatrix4fv(myShaders.worldMatrixLoc, 1, GL_FALSE, &wMatrix.m[0][0]);
	}

	if(myShaders.worldViewProjection != -1)
	{
		Matrix wvp =WorldMatrixCalc() * cam->Calculate_View_Matrix() * cam->Calculate_Projection_Matrix();
		glUniformMatrix4fv(myShaders.worldViewProjection, 1, GL_FALSE, &wvp.m[0][0]);
	}

	if(myShaders.a_uv != -1)
	{
		glEnableVertexAttribArray(myShaders.a_uv);
		//glUniformMatrix4fv(myShaders.worldViewProjection, 2, GL_FALSE, (void *)(12 * sizeof(float)));
		glVertexAttribPointer(myShaders.a_uv, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(16 * sizeof(float)));
	}

	//glDrawArrays(GL_TRIANGLES, 0, 3);
	unsigned short textureUnit = 0;
	// make active a texture unit	
	glActiveTexture(GL_TEXTURE0 + textureUnit); 

	// bind the texture to the currently active texture unit
	glBindTexture(GL_TEXTURE_2D, texture->getTexHandle());	 

	// set the uniform sampler
	glUniform1i(myShaders.uniformLocation, textureUnit);
	textureUnit++;

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, model_load->getm_hIndexBuffer());
	glDrawElements( GL_TRIANGLES, model_load->getIndicesNum(), GL_UNSIGNED_INT, (void*)0 );
	
	
	//unsigned short textureUnit = 0;
	//// make active a texture unit	
	//glActiveTexture(GL_TEXTURE0 + textureUnit); 

	//// bind the texture to the currently active texture unit
	//glBindTexture(GL_TEXTURE_2D, texture->getTexHandle());	 

	//// set the uniform sampler
	//glUniform1i(myShaders.uniformLocation, textureUnit);
	//textureUnit++;

	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	if (keyPressed & (1 << Globals::_KEY_W))
	{
		esLogMessage("Press Key W\n");
		cam->Move_Foward(deltaTime);
	}
	if (keyPressed & (1 << Globals::_KEY_A))
	{
		esLogMessage("Press key A\n");
		cam->Move_Left(deltaTime);
	}
	if (keyPressed & (1 << Globals::_KEY_S))
	{
		esLogMessage("Press key S\n");
		cam->Move_Backward(deltaTime);
	}
	if (keyPressed & (1 << Globals::_KEY_D))
	{
		esLogMessage("Press key D\n");
		cam->Move_Right(deltaTime);
	}
	if (keyPressed & (1 << Globals::_KEY_DOWN))
	{
		esLogMessage("Press Key DOWN\n");
		cam->Rotate_Down(deltaTime);
	}
	if (keyPressed & (1 << Globals::_KEY_UP))
	{
		esLogMessage("Press key UP\n");
		cam->Rotate_Up(deltaTime);
	}
	if (keyPressed & (1 << Globals::_KEY_LEFT))
	{
		esLogMessage("Press key LEFT\n");
		cam->Rotate_Left(deltaTime);
	}
	if (keyPressed & (1 << Globals::_KEY_RIGHT))
	{
		esLogMessage("Press key RIGHT\n");
		cam->Rotate_Right(deltaTime);
	}

}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{	
	if (bIsPressed)
	{
		switch (key)
		{		
			case Globals::KEY_W:
				keyPressed |= (1<<Globals::_KEY_W); //Al precionar la tecla  
			break;

			case Globals::KEY_A:
				keyPressed |= (1<<Globals::_KEY_A); //Al precionar la tecla  
			break;

			case Globals::KEY_S:
				keyPressed |= (1<<Globals::_KEY_S); //Al precionar la tecla  
			break;

			case Globals::KEY_D:
				keyPressed |= (1<<Globals::_KEY_D); //Al precionar la tecla  
			break;

			case Globals::KEY_LEFT:
				keyPressed |= (1<<Globals::_KEY_LEFT); //Al precionar la tecla  
			break;

			case Globals::KEY_RIGHT:
				keyPressed |= (1<<Globals::_KEY_RIGHT); //Al precionar la tecla  
			break;

			case Globals::KEY_UP:
				keyPressed |= (1<<Globals::_KEY_UP); //Al precionar la tecla  
			break;

			case Globals::KEY_DOWN:
				keyPressed |= (1<<Globals::_KEY_DOWN); //Al precionar la tecla  
			break;
		}
	}
	else
	{
		switch (key)
		{		
			case Globals::KEY_W:
				keyPressed &= ~(1<<Globals::_KEY_W); //Al precionar la tecla  
			break;

			case Globals::KEY_A:
				keyPressed &= ~(1<<Globals::_KEY_A); //Al precionar la tecla  
			break;

			case Globals::KEY_S:
				keyPressed &= ~(1<<Globals::_KEY_S); //Al precionar la tecla  
			break;

			case Globals::KEY_D:
				keyPressed &= ~(1<<Globals::_KEY_D); //Al precionar la tecla  
			break;

			case Globals::KEY_LEFT:
				keyPressed &= ~(1<<Globals::_KEY_LEFT); //Al precionar la tecla  
			break;

			case Globals::KEY_RIGHT:
				keyPressed &= ~(1<<Globals::_KEY_RIGHT); //Al precionar la tecla  
			break;

			case Globals::KEY_UP:
				keyPressed &= ~(1<<Globals::_KEY_UP); //Al precionar la tecla  
			break;

			case Globals::KEY_DOWN:
				keyPressed &= ~(1<<Globals::_KEY_DOWN); //Al precionar la tecla  
			break;
		}
	}
}

void CleanUp()
{
	glDeleteBuffers(1, &vboId);
	delete cam;
	delete model_load;
	delete texture;
	cam = NULL;
	model_load = NULL;
	texture = NULL;
}

int _tmain(int argc, _TCHAR* argv[])
{
#if 0
	Model * my_model = new Model();
	my_model->InitModel("Models/Woman1.nfg");
	delete my_model;
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
