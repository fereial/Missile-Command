#pragma once
#include "Game\Private\GameObject.h"
#include "Game\Private\GameObjectInventory.h"

HashMap<GameObject*, 256> mMap;

GameObjectInventory::GameObjectInventory()
{
}

GameObjectInventory::~GameObjectInventory()
{
}

void GameObjectInventory::Register(GameObject* pGO)
{
	mMap.InsertNoCheck(pGO);
}

void GameObjectInventory::Unregister(GameObject* pGO)
{
	mMap.Delete(pGO);
}

bool GameObjectInventory::Exists(Hash hash) const
{
	return (mMap.Find(hash) != nullptr);
}

GameObject* GameObjectInventory::Lookup(Hash hash)
{
	return mMap.Find(hash);
}

const GameObject* GameObjectInventory::Lookup(Hash hash) const
{
	return mMap.Find(hash);
}