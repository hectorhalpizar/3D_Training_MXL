//Definicion de la clase creada por Hector Alpizar
#include "stdafx.h"
#include "Camera.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "KeyboardHandler.h"

Camera::Camera()
{
	m_positionInfo = Vector3(0.0f, 0.0f, 0.0f);
	m_rotationInfo = Vector3(0.0f, 0.0f, 0.0f);
	setSpeed(1.0f);
	setNear(0.1f);
	setFar(500.0f);
	setFOV(1.0f);
}

Camera::Camera(float Near, float Far, float FOV, float Speed)
{
	setNear(Near);
	setFar(Far);
	setFOV(FOV);
	setSpeed(Speed);
}

Camera::~Camera()
{

}

void Camera::setNear(float value)
{
	m_near = value;
}

void Camera::setFar(float value)
{
	m_far = value;
}

void Camera::setFOV(float value)
{
	m_fov = value;
}

void Camera::setSpeed(float value)
{
	m_speed = value;
}

float Camera::getNear()
{
	return m_near;
}

float Camera::getFar()
{
	return m_far;
}

float Camera::getFOV()
{
	return m_fov;
}

float Camera::getSpeed()
{
	return m_speed;
}


void Camera::Move_Foward(float deltaTime)
{
	//MoveL = Vector4(0, 0, -deltaTime * speed,1)
	Vector4 moveZ = Vector4(0.0f, 0.0f, -deltaTime * SPEED_CAM * m_speed, 1);
	Vector4 worldMove = moveZ * Calculate_World_Matrix();
	m_positionInfo.x += worldMove.x;
	m_positionInfo.y += worldMove.y;
	m_positionInfo.z += worldMove.z;
}

void Camera::Move_Backward(float deltaTime)
{
	//MoveL = Vector4(0, 0, deltaTime * speed,1)
	Vector4 moveZ = Vector4(0.0f, 0.0f, deltaTime * SPEED_CAM * m_speed, 1);
	Vector4 worldMove = moveZ * Calculate_World_Matrix();
	m_positionInfo.x += worldMove.x;
	m_positionInfo.y += worldMove.y;
	m_positionInfo.z += worldMove.z;
}

void Camera::Move_Left(float deltaTime)
{
	Vector4 moveY = Vector4(-deltaTime * SPEED_CAM * m_speed, 0.0f, 0.0f, 1);
	Vector4 worldMove = moveY * Calculate_World_Matrix();
	m_positionInfo.x += worldMove.x;
	m_positionInfo.y += worldMove.y;
	m_positionInfo.z += worldMove.z;
}

void Camera::Move_Right(float deltaTime)
{
	Vector4 moveY = Vector4(deltaTime * SPEED_CAM * m_speed, 0.0f, 0.0f, 1);
	Vector4 worldMove = moveY * Calculate_World_Matrix();
	m_positionInfo.x += worldMove.x;
	m_positionInfo.y += worldMove.y;
	m_positionInfo.z += worldMove.z;
}

void Camera::Rotate_Up(float deltaTime)
{
	 float angle =(float) (m_rotationInfo.x * 180/M_PI);
	 if(angle<=90) //delimitamos rotacion arriba y abajo a 90º
     m_rotationInfo.x += (GLfloat)((deltaTime * SPEED_CAM_ROT * m_speed * M_PI/180));
}

void Camera::Rotate_Down(float deltaTime)
{
	float angle =(float) (m_rotationInfo.x * 180/M_PI);
	if(angle>=-90) //delimitamos rotacion arriba y abajo a 90º
	m_rotationInfo.x -= (GLfloat)((deltaTime * SPEED_CAM_ROT * m_speed * M_PI/180));

}

void Camera::Rotate_Left(float deltaTime)
{
	//float angle =(float) (m_rotationInfo.y * 180/M_PI);
	//if(angle<=90) //delimitamos rotacion arriba y abajo a 90º
    m_rotationInfo.y += (GLfloat)((deltaTime * SPEED_CAM_ROT * m_speed * M_PI/180));
}

void Camera::Rotate_Right(float deltaTime)
{
	//float angle =(float) (m_rotationInfo.y * 180/M_PI);
	//if(angle>=-90) //delimitamos rotacion arriba y abajo a 90º
    m_rotationInfo.y -= (GLfloat)((deltaTime * SPEED_CAM_ROT * m_speed * M_PI/180));
}

void Camera::Update(float deltaTime)
{
	if (KeyboardHandler::GetInstance()->isKeyPressed(Globals::_KEY_W))
	{
		//esLogMessage("Press Key W\n");
		Move_Foward(deltaTime);
	}

	if (KeyboardHandler::GetInstance()->isKeyPressed(Globals::_KEY_A))
	{
		//esLogMessage("Press key A\n");
		Move_Left(deltaTime);
	}

	if (KeyboardHandler::GetInstance()->isKeyPressed(Globals::_KEY_S))
	{
		//esLogMessage("Press key S\n");
		Move_Backward(deltaTime);
	}

	if (KeyboardHandler::GetInstance()->isKeyPressed(Globals::_KEY_D))
	{
		//esLogMessage("Press key D\n");
		Move_Right(deltaTime);
	}

	if (KeyboardHandler::GetInstance()->isKeyPressed(Globals::_KEY_DOWN))
	{
		//esLogMessage("Press Key DOWN\n");
		Rotate_Down(deltaTime);
	}

	if (KeyboardHandler::GetInstance()->isKeyPressed(Globals::_KEY_UP))
	{
		//esLogMessage("Press key UP\n");
		Rotate_Up(deltaTime);
	}

	if (KeyboardHandler::GetInstance()->isKeyPressed(Globals::_KEY_LEFT))
	{
		//esLogMessage("Press key LEFT\n");
		Rotate_Left(deltaTime);
	}

	if (KeyboardHandler::GetInstance()->isKeyPressed(Globals::_KEY_RIGHT))
	{
		//esLogMessage("Press key RIGHT\n");
		Rotate_Right(deltaTime);
	}
}

Matrix Camera::Calculate_View_Matrix()
{
	Matrix inverseMatrix;
	Matrix rotationXMatrix;
	Matrix rotationYMatrix;
	Matrix rotationZMatrix;
	Matrix translationMatrix;

	rotationXMatrix.SetIdentity();
	rotationYMatrix.SetIdentity();
	translationMatrix.SetIdentity();

	rotationXMatrix.SetRotationX(-m_rotationInfo.x);
	rotationYMatrix.SetRotationY(-m_rotationInfo.y);	
	translationMatrix.SetTranslation(-m_positionInfo.x, -m_positionInfo.y, -m_positionInfo.z);

    //inverseMatrix = rotationXMatrix * rotationYMatrix * translationMatrix;//NO
    inverseMatrix = translationMatrix * rotationYMatrix * rotationXMatrix;//OK

	return inverseMatrix;
}

Matrix Camera::Calculate_World_Matrix()
{
	Matrix rotationXMatrix;
	Matrix rotationYMatrix;
	Matrix translationMatrix;

	Matrix worldMatrix;

	rotationXMatrix.SetIdentity();
	rotationYMatrix.SetIdentity();
	
	translationMatrix.SetIdentity();	
	rotationXMatrix.SetRotationX(m_rotationInfo.x);
	rotationYMatrix.SetRotationY(m_rotationInfo.y);
	
	worldMatrix = rotationXMatrix * rotationYMatrix * translationMatrix;

	return worldMatrix;
}

Matrix Camera::Calculate_Projection_Matrix()
{
	Matrix tmp;
	//tmp.SetPerspective(1.0f, (float)Globals::screenWidth/Globals::screenHeight, 0.1f, 500.0f);
	tmp.SetPerspective(m_fov, (float)Globals::screenWidth/Globals::screenHeight, m_near, m_far);
	return tmp ;
}