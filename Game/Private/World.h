#pragma once
#include <vector>

#include "Game\Private\Singleton.h"
#include "GameObjectInventory.h"
#include "HashMap.h"
#include "COGMeteoriteController.h"
#include "COGmeteoriteSpwaner.h"
#include <vector>
#include <string>



class World : public Singleton<World>
{
public:
	World();
	~World();
	void Create(exEngineInterface* pEngine);
	void Destroy();
	void Update(float fDeltaT);
	GameObject* CreateMissile();
	GameObject* SpawnMissile();
	GameObject* SpawnPlayer();
	GameObject* SpawnBang(float x ,float y);
	GameObject* CreatePaddle(exEngineInterface* playEngine, float posX, float posY);
	GameObject* Ground(exEngineInterface* playEngine, float posX, float posY);
	GameObject* Bang(float posX, float posY);
	GameObject* SpawnMeteoriteSpawner();
	GameObject* SpawnMeteorController();
	GameObject* CreateMeteorite();
	friend class Singleton<World>;

	exEngineInterface* playEngine;
	int missileItem;
	int bangItem;
	int metioriteItem;
	GameObjectInventory* gameInv;
	
	


private:

	std::vector<GameObject*> mGameObjects;

};
World* Singleton<World>::instance = nullptr;

