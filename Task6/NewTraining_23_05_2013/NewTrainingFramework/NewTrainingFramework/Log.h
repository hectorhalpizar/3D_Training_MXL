#ifndef __LOG__
#define __LOG__

class Log
{
protected:
	Log(){}
	~Log(){}
	
	Log(const Log &){}
	Log& operator = (const Log &) {}

	static Log * ms_pInstance;

public:
	static Log * GetInstance()
	{
		if (ms_pInstance == NULL)
			ms_pInstance = new Log();

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

	void printMessage(const char * TAG, const char * MSG, ...);
};

#endif