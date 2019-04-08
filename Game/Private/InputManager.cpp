#include "InputManager.h"


InputManager::InputManager()
{
	posY = 0;
	posX = 0;
	shoot = false;

}

InputManager::~InputManager()
{
}

void InputManager::InputRegister()
{
	
	buttons = SDL_GetMouseState(&xPos, &yPos);

	

	if ((buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0)
	{
		posX = xPos;
		posY = yPos;
		shoot = true;
	}
	else 
	{
		shoot = false;
	}
}

void InputManager::InputAssignation()
{

	
}
