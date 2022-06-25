//Encabezado de la clase creada por Hector Alpizar
#ifndef __CAMERA__
#define __CAMERA__

#include "../Utilities/Math.h"

#define SPEED_CAM		(2)
#define SPEED_CAM_ROT	(40)

class Camera
{
public:	
	Vector3 m_positionInfo;
	Vector3 m_rotationInfo;

	Camera();
	~Camera();

	void Move_Foward(float deltaTime);
	void Move_Backward(float deltaTime);
	void Move_Left(float deltaTime);
	void Move_Right(float deltaTime);

	void Rotate_Up(float deltaTime);
	void Rotate_Down(float deltaTime);
	void Rotate_Left(float deltaTime);
	void Rotate_Right(float deltaTime);

	Matrix Calculate_View_Matrix();
	Matrix Calculate_World_Matrix();
	Matrix Calculate_Projection_Matrix();
};

#endif
