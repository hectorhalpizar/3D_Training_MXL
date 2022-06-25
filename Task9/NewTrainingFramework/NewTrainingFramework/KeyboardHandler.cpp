#include "stdafx.h"
#include "KeyboardHandler.h"
#include "Globals.h"

KeyboardHandler * KeyboardHandler::ms_pInstance = NULL;

void KeyboardHandler::check(unsigned char key, bool isPressed)
{
	if (isPressed)
	{
		switch (key)
		{		
			case Globals::KEY_W:
				keyPressed |= (1<<Globals::_KEY_W); //Al precionar la tecla  
			break;

			case Globals::KEY_A:
				keyPressed |= (1<<Globals::_KEY_A); //Al precionar la tecla  
			break;

			case Globals::KEY_S:
				keyPressed |= (1<<Globals::_KEY_S); //Al precionar la tecla  
			break;

			case Globals::KEY_D:
				keyPressed |= (1<<Globals::_KEY_D); //Al precionar la tecla  
			break;

			case Globals::KEY_LEFT:
				keyPressed |= (1<<Globals::_KEY_LEFT); //Al precionar la tecla  
			break;

			case Globals::KEY_RIGHT:
				keyPressed |= (1<<Globals::_KEY_RIGHT); //Al precionar la tecla  
			break;

			case Globals::KEY_UP:
				keyPressed |= (1<<Globals::_KEY_UP); //Al precionar la tecla  
			break;

			case Globals::KEY_DOWN:
				keyPressed |= (1<<Globals::_KEY_DOWN); //Al precionar la tecla  
			break;
		}
	}
	else
	{
		switch (key)
		{		
			case Globals::KEY_W:
				keyPressed &= ~(1<<Globals::_KEY_W); //Al precionar la tecla  
			break;

			case Globals::KEY_A:
				keyPressed &= ~(1<<Globals::_KEY_A); //Al precionar la tecla  
			break;

			case Globals::KEY_S:
				keyPressed &= ~(1<<Globals::_KEY_S); //Al precionar la tecla  
			break;

			case Globals::KEY_D:
				keyPressed &= ~(1<<Globals::_KEY_D); //Al precionar la tecla  
			break;

			case Globals::KEY_LEFT:
				keyPressed &= ~(1<<Globals::_KEY_LEFT); //Al precionar la tecla  
			break;

			case Globals::KEY_RIGHT:
				keyPressed &= ~(1<<Globals::_KEY_RIGHT); //Al precionar la tecla  
			break;

			case Globals::KEY_UP:
				keyPressed &= ~(1<<Globals::_KEY_UP); //Al precionar la tecla  
			break;

			case Globals::KEY_DOWN:
				keyPressed &= ~(1<<Globals::_KEY_DOWN); //Al precionar la tecla  
			break;
		}
	}
}

bool KeyboardHandler::isKeyPressed(Globals::Key _keyPressed)
{
	//return (keyPressed & (1 << _keyPressed)) ? true : false;
	if (keyPressed & (1 << _keyPressed))
		return true;
	else
		return false;

}