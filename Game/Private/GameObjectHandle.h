#pragma once

#include <list>
#include <string>
#include <functional>
#include "Game\Private\HashMap.h"
#include "Game\Private\GameObjectInventory.h"
class GameObjectHandle
{
public:
	Hash mHash;

public:
	bool IsValid() const;
	GameObject* Get() const;
	GameObjectInventory gGameObjectInventory;
	

};