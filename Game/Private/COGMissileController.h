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
class COGMissileController : public Component 
{
public:
	COGMissileController(GameObject* pGO);
	~COGMissileController() = default;
	void Initialize();
	void Destroy();
	void Update();
	void SpawnMissle(Vector2 initialPosition, Vector2 finalPos);
	static std::vector<COGMissileController*> mMissileController;
	Vector2 Direction(Vector2 finalPos,Vector2 initPos);

	
	virtual ComponentType GetType() const;
private:
	COGTransform* mTransfrom;
	COGPlayerController* mPlayerController;
	COGLineShape* mLineShape;
	COGPhysics* mPhysics;
	Vector2 FinalPosition;
	GameObjectHandle mHandle;
	Vector2 refFinalPos;
};