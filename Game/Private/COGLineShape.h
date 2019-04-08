#pragma once
#include "Game/Private/Component.h"
#include "Game/Private/COGShape.h"
#include "Game\Private\COGTransform.h"
#include "Game\Private\GameObject.h"
#include "Game/Engine/Public/EngineInterface.h"
#include "Game/Engine/Public/EngineTypes.h"
#include "Math.h"
#include "Game\Private\InputManager.h"
#include "Game\Private\COGMissileController.h"
#include "Game\Private\COGPhysics.h"
#include "GameObjectHandle.h"

class COGMissileController;
class Transform;
class COGMissileController;
class COGLineShape : public COGShape
{
public:
	

	COGLineShape(GameObject* pGO, exEngineInterface* pPlayEngine);
	~COGLineShape();

	void Update(Vector2 positionOther, Vector2 finalPos);

	virtual ComponentType GetType() const;

	virtual void Render() override;
	void Initialize();
	void Destroy();
private:

	bool goBoom;
	bool makeBang;
	exColor c;
	exEngineInterface* mPlayEngine;
	Vector2 mPositionOther;
	COGTransform* mTransfrom;
	Vector2 finalPos;
	COGMissileController* mMissileControl;
	GameObjectHandle mHandle;
	
};
