#ifndef __OBJECT__
#define __OBJECT__

#include "Texture.h"
#include "Model.h"
#include "Shaders.h"
#include "Water.h"
#include "../Utilities/Math.h"

class Object
{
public:
	Object();
	void set(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, float tileFactor);
	~Object();

	void Update(float deltaTime);
	void Draw();
	void Init();

	void setID(unsigned int id);
	unsigned int getID();

	void set2DTexAmount(int value);
	int get2DTexAmount();

	void setCubeTexAmount(int value);
	int getCubeTexAmount();

	void setFogColor(float r, float g, float b);
	Vector3 getFogColor();

	void setFogStart(float value);
	float getFogStart();

	void setFogRange(float value);
	float getFogRange();

	void setLightAmount(int value);
	int getLightAmount();

	Vector3 m_fogColor;

	Matrix GetWorldMatrix();

	Model * m_modelPtr;

	Texture ** m_tex2DPtrPtr;
	Texture ** m_texCubePtrPtr;

	Shaders * m_shaderPtr;

	Matrix m_position, m_rotationX, m_rotationY, m_rotationZ, m_scale;
	
	static short indexTex;
	
	Vector3 * light_color;
	Vector3 * light_PosDir;
	int * light_Id;
	int * light_Type;
	int * light_move_type;
	float * light_radius;
	float * speed;
	float * specular_power;

	int waterId;

	float getCurrentDeltaTime() { return m_currentDeltaTime; }

	void setPosition(float newX, float newY, float newZ) { m_posX = newX; m_posY = newY; m_posZ = newZ; } 

	float getX() { return m_posX; }
	float getY() { return m_posY; }
	float getZ() { return m_posZ; }

private:
	unsigned int m_ID;
	int m_tex2DAmount, m_texCubeAmount, m_lightsAmount;

	float m_posX, m_posY, m_posZ,
		m_rotX, m_rotY, m_rotZ,
		m_scaleX, m_scaleY, m_scaleZ, m_tileFactor,
		m_fogStart, m_fogRange, m_currentDeltaTime;

	//Vector3 * light_color;
	//Vector3 * light_PosDir;
	//int * light_Id;
	//int * light_Type;
	//int * light_move_type;
	//float * light_radius;
	//float * speed;
	//float * specular_power;
};
#endif