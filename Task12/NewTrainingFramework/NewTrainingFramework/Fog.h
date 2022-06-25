#ifndef __FOG__
#define __FOG__

#include "../Utilities/Math.h"
class Fog
{
protected:
	Fog() {}
	~Fog() {}

	Fog(const Fog &){}
	Fog& operator = (const Fog &) {}

	static Fog * ms_pInstance;
public:
	Vector3 m_color;
	float m_start;
	float m_range;

	static Fog * GetInstance()
	{
		if (ms_pInstance == NULL)
			ms_pInstance = new Fog();

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
