//Definicion de la clase creada por Hector Alpizar
#include "stdafx.h"
#include "Camera.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Globals.h"

Camera::Camera()
{
	m_positionInfo = Vector3(0.0f, 0.0f, 3.0f);
	m_rotationInfo = Vector3(0.0f, 0.0f, 0.0f);
}

Camera::~Camera()
{

}

void Camera::Move_Foward(float deltaTime)
{
	//MoveL = Vector4(0, 0, -deltaTime * speed,1)
	Vector4 moveZ = Vector4(0.0f, 0.0f, -deltaTime * SPEED_CAM, 1);
	Vector4 worldMove = moveZ * Calculate_World_Matrix();
	m_positionInfo.x += worldMove.x;
	m_positionInfo.y += worldMove.y;
	m_positionInfo.z += worldMove.z;
}

void Camera::Move_Backward(float deltaTime)
{
	//MoveL = Vector4(0, 0, deltaTime * speed,1)
	Vector4 moveZ = Vector4(0.0f, 0.0f, deltaTime * SPEED_CAM, 1);
	Vector4 worldMove = moveZ * Calculate_World_Matrix();
	m_positionInfo.x += worldMove.x;
	m_positionInfo.y += worldMove.y;
	m_positionInfo.z += worldMove.z;
}

void Camera::Move_Left(float deltaTime)
{
	Vector4 moveY = Vector4(-deltaTime * SPEED_CAM, 0.0f, 0.0f, 1);
	Vector4 worldMove = moveY * Calculate_World_Matrix();
	m_positionInfo.x += worldMove.x;
	m_positionInfo.y += worldMove.y;
	m_positionInfo.z += worldMove.z;
}

void Camera::Move_Right(float deltaTime)
{
	Vector4 moveY = Vector4(deltaTime * SPEED_CAM, 0.0f, 0.0f, 1);
	Vector4 worldMove = moveY * Calculate_World_Matrix();
	m_positionInfo.x += worldMove.x;
	m_positionInfo.y += worldMove.y;
	m_positionInfo.z += worldMove.z;
}

void Camera::Rotate_Up(float deltaTime)
{
	 float angle =(float) (m_rotationInfo.x * 180/M_PI);
     if(angle<=90) //delimitamos rotacion arriba y abajo a 90º
     m_rotationInfo.x += (GLfloat)((deltaTime * SPEED_CAM_ROT * M_PI/180));
}

void Camera::Rotate_Down(float deltaTime)
{
	float angle =(float) (m_rotationInfo.x * 180/M_PI);
	if(angle>=-90) //delimitamos rotacion arriba y abajo a 90º
	m_rotationInfo.x -= (GLfloat)((deltaTime * SPEED_CAM_ROT * M_PI/180));

}

void Camera::Rotate_Left(float deltaTime)
{
	float angle =(float) (m_rotationInfo.y * 180/M_PI);
    if(angle<=90) //delimitamos rotacion arriba y abajo a 90º
    m_rotationInfo.y += (GLfloat)((deltaTime * SPEED_CAM_ROT * M_PI/180));
}

void Camera::Rotate_Right(float deltaTime)
{
	float angle =(float) (m_rotationInfo.y * 180/M_PI);
	if(angle>=-90) //delimitamos rotacion arriba y abajo a 90º
    m_rotationInfo.y -= (GLfloat)((deltaTime * SPEED_CAM_ROT * M_PI/180));
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
	tmp.SetPerspective(1.0f, (float)Globals::screenWidth/Globals::screenHeight, 0.1f, 500.0f);
	return tmp ;
}