#ifndef __SCENE_MANAGER__
#define __SCENE_MANAGER__
#include "Object.h"
#include "Light.h"
#include "Camera.h"

class SceneManager
{
private:
	Object * m_objPtr;
	Camera * m_CameraPtrObj;

	Light * m_lights;

	int m_objAmount;
	int m_lightsAmount;

	int readFile(const char * filePath);


protected:
	SceneManager() {}
	~SceneManager();

	SceneManager(const SceneManager &){}
	SceneManager& operator = (const SceneManager &) {}

	static SceneManager * ms_pInstance;

public:

	LightConst m_lightConst;

	void Init();

	void Update(float deltaTime);

	void Draw();

	void setLightsAmount(int value);

	int getLightsAmount();
	
	Camera * getCamera();

	Light * getLight(int byId);

	static SceneManager * GetInstance()
	{
		if (ms_pInstance == NULL)
			ms_pInstance = new SceneManager();

		return ms_pInstance;
	}

	static void DestroyInstance()
	{
		if (ms_pInstance)
		{
			delete ms_pInstance;
			ms_pInstance = NULL;
		}
	}
};

#endif
