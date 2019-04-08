#pragma once
#include "COGPlayerController.h"
#include "COGTransform.h"
#include "GameObject.h"
#include "COGMissileController.h"
#include "Game\Private\InputManager.h"
#include "Game\Private\World.h"

COGPlayerController::COGPlayerController(GameObject* pGO, exEngineInterface* playEngine)
	: Component(pGO)
	, mPlayEngine(playEngine)
{
	timer = 0;
}


void COGPlayerController::Initialize()
{
	 AddToComponentVector(mPlayerControllers);

}

void COGPlayerController::Destroy()
{
	RemoveFromComponentVector(mPlayerControllers);
}

void COGPlayerController::Update(float fDelta)
{
	timer -= fDelta;
	InputManager* mInputM = InputManager::getinstance();
	mInputM->InputRegister();

	if (mInputM->shoot == true && timer < 0)
	{
		Vector2 initialPosition;
		initialPosition.x = 400;
		initialPosition.y = 585;
		mousePos.x = mInputM->posX;
		mousePos.y = mInputM->posY;
		GameObject* missile = World::getinstance()->CreateMissile();
		COGMissileController* pMissileController = missile->FindComponent<COGMissileController>(ComponentType::MissileController);

		pMissileController->SpawnMissle(initialPosition, mousePos);
		timer = 0.6f;
	}
}

ComponentType COGPlayerController::GetType() const
{
	return ComponentType::PlayerController;
}




std::vector<COGPlayerController*> COGPlayerController::mPlayerControllers;