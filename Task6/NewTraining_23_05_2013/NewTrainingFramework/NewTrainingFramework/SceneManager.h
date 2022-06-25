#ifndef __SCENE_MANAGER__
#define __SCENE_MANAGER__
#include "Object.h"
#include "Light.h"
#include "Camera.h"

class SceneManager
{
private:
	Object * m_objPtr;
	Light * m_lightPtr;
	Camera * m_CameraPtrObj;

	int m_objAmount;

	int readFile(const char * filePath);


protected:
	SceneManager() {}
	~SceneManager();

	SceneManager(const SceneManager &){}
	SceneManager& operator = (const SceneManager &) {}

	static SceneManager * ms_pInstance;

public:
	void Init();

	void Update(float deltaTime);

	void Draw();
	
	Camera * getCamera();

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
