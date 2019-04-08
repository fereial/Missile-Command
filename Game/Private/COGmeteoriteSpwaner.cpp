#include "COGmeteoriteSpwaner.h"
#include "COGTransform.h"
#include "GameObject.h"
#include "COGMissileController.h"
#include "Game\Private\InputManager.h"
#include "Game\Private\World.h"
#include <cstdlib> 
#include <ctime> 
#include <iostream>
COMeteoriteSpawner::COMeteoriteSpawner(GameObject * pGO, exEngineInterface * mPlayEngine)
	:Component(pGO),
	mPlayEngine(mPlayEngine)
{
	timer = 0;
}

void COMeteoriteSpawner::Initialize()
{
	AddToComponentVector(mMeteoriteSpawner);
}

void COMeteoriteSpawner::Destroy()
{
	RemoveFromComponentVector(mMeteoriteSpawner);
}

void COMeteoriteSpawner::Update(float fDelta)
{
	timer -= fDelta;
	if(timer <= 0) 
	{
		GameObject* meteorite = World::getinstance()->CreateMeteorite();
		COGMeteoriteController* pMeteoriteController = meteorite->FindComponent<COGMeteoriteController>(ComponentType::MeteoriteController);

		pMeteoriteController->SpawnMissle();
		timer = 3;
	}
}

ComponentType COMeteoriteSpawner::GetType() const
{
	return ComponentType::MeteoriteSpawner;
}
std::vector<COMeteoriteSpawner*> COMeteoriteSpawner::mMeteoriteSpawner;