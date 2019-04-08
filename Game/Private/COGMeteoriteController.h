#pragma once
#include "COGTransform.h"
#include "COGPlayerController.h"
#include "COGLineShape.h"
#include "COGPhysics.h"
#include "Component.h"
#include "ComponentType.h"
#include "Math.h"
#include "GameObjectHandle.h"

class Trasnfrom;
class COGPlayerController;
class COGPhysics;
class COGLineShape;
class World;
class COGMeteoriteController : public Component
{
public:
	COGMeteoriteController(GameObject* pGO);
	~COGMeteoriteController() = default;
	void Initialize();
	void Destroy();
	void SpawnMissle();
	void Update();
	static std::vector<COGMeteoriteController*> mMeteoriteController;
	Vector2 Direction();


	virtual ComponentType GetType() const;
private:
	COGTransform * mTransfrom;
	COGPlayerController* mPlayerController;
	COGLineShape* mLineShape;
	COGPhysics* mPhysics;
	Vector2 FinalPosition;
	GameObjectHandle mHandle;
};