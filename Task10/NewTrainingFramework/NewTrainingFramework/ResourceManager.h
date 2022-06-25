#ifndef __RESOURCE_MANAGER__
#define __RESOURCE_MANAGER__

#include "Model.h"
#include "Texture.h"
#include "Shaders.h"

class ResourceManager
{
private:
	int m_modelsAmount;
	int m_tex2DAmount;
	int m_texCubeAmount;
	int m_shadersAmount;
	Model * m_modelsPtr;
	Texture * m_tex2DPtr;
	Texture * m_texCubePtr;
	Shaders * m_shaderPtr;

	char readFile(const char * filePath);
protected:
	ResourceManager() {}
	~ResourceManager();

	ResourceManager(const ResourceManager &){}
	ResourceManager& operator = (const ResourceManager &) {}

	static ResourceManager * ms_pInstance;

public:
	Model * GetModel(unsigned int byID);

	Texture * GetTexure2D(unsigned int byID);

	Texture * GetTexureCube(unsigned int byID);

	Shaders * GetShaders(unsigned int byID);
	
	void Init();
	
	static ResourceManager * GetInstance()
	{
		if (ms_pInstance == NULL)
			ms_pInstance = new ResourceManager();

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