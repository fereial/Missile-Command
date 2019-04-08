#pragma once
#include "Game\Private\GameObjectHandle.h"
#include "World.h"
bool GameObjectHandle::IsValid() const
{
	GameObjectInventory* gInvet =  World::getinstance()->gameInv;
	return gInvet->Exists(mHash);
}

GameObject* GameObjectHandle::Get() const
{
	return const_cast<GameObject*>(gGameObjectInventory.Lookup(mHash));
}
