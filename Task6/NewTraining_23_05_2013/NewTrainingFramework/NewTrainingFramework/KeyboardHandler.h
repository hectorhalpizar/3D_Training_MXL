#ifndef __KEYBOARD_HANDLER__
#define __KEYBOARD_HANDLER__

#include "Globals.h"

class KeyboardHandler
{
private:
	int keyPressed;

protected:
	KeyboardHandler() 
	{
		keyPressed = 0;
	}
	~KeyboardHandler() {}

	KeyboardHandler(const KeyboardHandler &){}
	KeyboardHandler& operator = (const KeyboardHandler &) {}

	static KeyboardHandler * ms_pInstance;

public:
	static KeyboardHandler * GetInstance()
	{
		if (ms_pInstance == NULL)
			ms_pInstance = new KeyboardHandler();

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

	void check(unsigned char key, bool isPressed);

	bool isKeyPressed(Globals::Key _keyPressed);
	
};
#endif