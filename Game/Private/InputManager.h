#pragma once
#include "Game\Private\Singleton.h"
#include "Game/Engine\Public\SDL.h"
class InputManager : public Singleton<InputManager>
{
public:
	InputManager();
	~InputManager();
	float posX;
	float posY;
	int xPos;
	int yPos;
	bool shoot;
	unsigned int buttons;
	void InputRegister();
	void InputAssignation();
	
	friend class Singleton<InputManager>;
};

InputManager* Singleton<InputManager>::instance = nullptr;