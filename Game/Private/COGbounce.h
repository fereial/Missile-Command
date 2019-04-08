#pragma once
#include "Game/Private/Component.h"
#include "Game/Private/IPhysicsCollisionEvent.h"
#include "Game\Private\COGPhysics.h"
#include "Game\Private\GameObject.h"


// COGBounce - where we make the ball bounce
class COGBounce : public Component, public IPhysicsCollisionEvent
{
public:

	COGBounce(GameObject* pGO);
	~COGBounce() = default;

	virtual ComponentType GetType() const;

	virtual void OnCollision(COGPhysics* pMe, COGPhysics* pOther) override;

	virtual void Initialize() override;
	
};