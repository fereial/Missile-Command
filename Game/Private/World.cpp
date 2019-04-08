#include "World.h"
#include "Game/Private/GameObject.h"
#include "Game/Private/COGPhysics.h"
#include "Game\Engine\Public\EngineInterface.h"
#include "Game\Engine\Public\EngineTypes.h"
#include "Game\Private\COGPlayerController.h"
#include "Game\Private\COGbounce.h"
#include "Game\Private\COGScore.h"
#include "Game\Private\COGMissileController.h"
#include "Game\Private\COGLineShape.h"
#include "COGBoxShape.h"
#include "COGCircleShape.h"


World::World()
{
	gameInv = new GameObjectInventory();
	HashMap<GameObjectHandle, 256> gameObjectInventory;
	missileItem = 1;
	bangItem = 1;
	metioriteItem = 1;

}


World::~World()
{
}


void World::Create(exEngineInterface* pEngine)
{
	playEngine = pEngine;

	mGameObjects.push_back(SpawnPlayer());
	mGameObjects.push_back(SpawnMeteoriteSpawner());
	mGameObjects.push_back(CreatePaddle(playEngine, 150, 565));
	mGameObjects.push_back(CreatePaddle(playEngine, 700, 565));
	mGameObjects.push_back(CreatePaddle(playEngine, 250, 565));
	mGameObjects.push_back(CreatePaddle(playEngine, 550, 565));
	mGameObjects.push_back(Ground(playEngine, 400, 620));

}

void World::Destroy()
{
	for (GameObject* pGameObject : mGameObjects)
	{
		delete pGameObject;
	}

	mGameObjects.clear();
}

void World::Update(float fDeltaT)
{
	

	// run simulation first
	for (COGPhysics* pPhysics : COGPhysics::mPhysicsComponents)
	{
		pPhysics->Update(fDeltaT);
	}
	
	for (COGPlayerController*pPlayerController : COGPlayerController::mPlayerControllers)
	{
		pPlayerController->Update(fDeltaT);
	}
	for (COGMissileController*pMissileController : COGMissileController::mMissileController) 
	{
		pMissileController->Update();
	}

	for (COMeteoriteSpawner* pMeteoriteSpawner : COMeteoriteSpawner::mMeteoriteSpawner) 
	{
		pMeteoriteSpawner->Update(fDeltaT);
	}
	for (COGMeteoriteController* pMeteoriteController : COGMeteoriteController::mMeteoriteController) 
	{
		pMeteoriteController->Update();
	}

	// then render everything
	for (COGShape* pShape : COGShape::mShapeComponents)
	{
		pShape->Render();
	}

	
}

GameObject* World::SpawnPlayer()
{
	GameObject* pLine = new GameObject(s_hash("Player1"), gameInv);

	COGPlayerController* pPlayerController = new COGPlayerController(pLine, playEngine);
	pLine->AddComponent(pPlayerController);

	pLine->Initialize();

	return pLine;
}

GameObject * World::SpawnBang(float x, float y)
{
	GameObject* p = Bang(x,y);
	mGameObjects.push_back(p);

	return p;
}

GameObject * World::SpawnMissile()
{
	
	GameObject* pLine = new GameObject(s_hash("Miissle" + (missileItem += 1)),gameInv);
	
	COGTransform* pTransform = new COGTransform(pLine,0,600);
	pLine->AddComponent(pTransform);
	
	COGLineShape* pLineShape = new COGLineShape(pLine, playEngine);
	pLine->AddComponent(pLineShape);

	COGPhysics* pPhysics = new COGPhysics(pLine, true,0,0);
	pLine->AddComponent(pPhysics);

	COGMissileController* pMissileController = new COGMissileController(pLine);
	pLine->AddComponent(pMissileController);
		
	pLine->Initialize();
	
	return pLine;
}
GameObject* World::CreateMissile()
{
	GameObject* p = SpawnMissile();
	mGameObjects.push_back(p);

	return p;
}

GameObject* World::CreatePaddle(exEngineInterface* pEngine, float posX, float posY)
{
	const float fPaddleWidth = 100.0f;
	const float fPaddleHeight = 50.0f;


	GameObject* pPaddle = new GameObject(s_hash("House" + missileItem), gameInv);

	missileItem++;

	COGTransform* pTransform = new COGTransform(pPaddle,posX,posY);
	pPaddle->AddComponent(pTransform);

	COGBoxShape* pBoxShape = new COGBoxShape(pPaddle, fPaddleWidth, fPaddleHeight,pEngine,1);
	pPaddle->AddComponent(pBoxShape);

	COGPhysics* pPhysics = new COGPhysics(pPaddle, false,0,0);
	pPaddle->AddComponent(pPhysics);

	
	
	pPaddle->Initialize();

	return pPaddle;
}

GameObject * World::Ground(exEngineInterface * playEngine, float posX, float posY)
{
	const float fPaddleWidth = 800.0f;
	const float fPaddleHeight = 50.0f;


	GameObject* pPaddle = new GameObject(s_hash("House" + missileItem), gameInv);

	missileItem++;

	COGTransform* pTransform = new COGTransform(pPaddle, posX, posY);
	pPaddle->AddComponent(pTransform);

	COGBoxShape* pBoxShape = new COGBoxShape(pPaddle, fPaddleWidth, fPaddleHeight, playEngine,2);
	pPaddle->AddComponent(pBoxShape);

	COGPhysics* pPhysics = new COGPhysics(pPaddle, true, 0, 0);
	pPaddle->AddComponent(pPhysics);



	pPaddle->Initialize();

	return pPaddle;
}




GameObject* World::Bang( float posX, float posY)
{
	const float fBallRadius = 5.0f;

	GameObject* pBall = new GameObject(s_hash("Bang" + (bangItem +=1 )), gameInv);

	bangItem++;
		
	COGTransform* pTransform = new COGTransform(pBall,posX,posY);
	pBall->AddComponent(pTransform);

	COGCircleShape* pBoxShape = new COGCircleShape(pBall, fBallRadius, playEngine);
	pBall->AddComponent(pBoxShape);

	COGPhysics* pPhysics = new COGPhysics(pBall, true,0,0);
	pBall->AddComponent(pPhysics);

	
	pBall->Initialize();

	return pBall;
}

GameObject * World::SpawnMeteoriteSpawner()
{
	GameObject* pMeteoriteSpawner = new GameObject(s_hash("MeteoriSpawner"), gameInv);

	COMeteoriteSpawner* pSpawner = new COMeteoriteSpawner(pMeteoriteSpawner, playEngine);
	pMeteoriteSpawner->AddComponent(pSpawner);

	pMeteoriteSpawner->Initialize();
	
	return pMeteoriteSpawner;
}

GameObject * World::SpawnMeteorController()
{
	GameObject* pMeteoritController = new GameObject(s_hash("Meteorite" + metioriteItem + 1), gameInv);

	metioriteItem++;

	COGTransform* pTransform = new COGTransform(pMeteoritController, 0, 600);
	pMeteoritController->AddComponent(pTransform);

	COGLineShape* pLineShape = new COGLineShape(pMeteoritController, playEngine);
	pMeteoritController->AddComponent(pLineShape);

	COGPhysics* pPhysics = new COGPhysics(pMeteoritController, true, 0, 0);
	pMeteoritController->AddComponent(pPhysics);

	COGMeteoriteController* pMissileController = new COGMeteoriteController(pMeteoritController);
	pMeteoritController->AddComponent(pMissileController);

	pMeteoritController->Initialize();

	return pMeteoritController;

}

GameObject * World::CreateMeteorite()
{
	GameObject* p = SpawnMeteorController();
	mGameObjects.push_back(p);

	return p;
	
}



