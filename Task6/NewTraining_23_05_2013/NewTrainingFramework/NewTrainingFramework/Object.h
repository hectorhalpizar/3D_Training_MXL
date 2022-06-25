#ifndef __OBJECT__
#define __OBJECT__

#include "Texture.h"
#include "Model.h"
#include "Shaders.h"
#include "../Utilities/Math.h"

class Object
{
public:
	Object();
	void set(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ);
	~Object();

	void Update();
	void Draw();
	void Init();

	void setID(unsigned int id);
	unsigned int getID();

	void set2DTexAmount(int value);
	int get2DTexAmount();

	void setCubeTexAmount(int value);
	int getCubeTexAmount();

	Matrix GetWorldMatrix();

	Model * m_modelPtr;

	Texture ** m_tex2DPtrPtr;
	Texture ** m_texCubePtrPtr;

	Shaders * m_shaderPtr;

	Matrix m_position, m_rotationX, m_rotationY, m_rotationZ, m_scale;

	static short indexTex;
private:
	unsigned int m_ID;
	int m_tex2DAmount, m_texCubeAmount;

	float m_posX, m_posY, m_posZ,
		m_rotX, m_rotY, m_rotZ,
		m_scaleX, m_scaleY, m_scaleZ;
};
#endif