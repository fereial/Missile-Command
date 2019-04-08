#pragma once
#include "Game/Private/Component.h"
#include "Game/Private/GameObject.h"
#include "Game/Private/IPhysicsCollisionEvent.h"
#include "Game\Private\Math.h"
#include "COGLineShape.h"

class COGTransform;
class COGBoxShape;
class COGLineShape;
class COGCircleShape;
class COGMeteoriteController;

// COGPhysics - lets move around
class COGPhysics : public Component
{
public:

	static std::vector<COGPhysics*> mPhysicsComponents;

public:

	COGPhysics(GameObject* pGO, bool bGenerateCollisionEvents, float vX, float vY);
	~COGPhysics() = default;
	virtual ComponentType GetType() const;

	virtual void Initialize() override;

	virtual void Destroy() override;
	virtual void Update(float fDeltaT);

	bool IsColliding(COGPhysics* pOther);
	void AddCollisionEventListener(IPhysicsCollisionEvent* pEvent);

	
	Vector2 mVelocity;
	int collisionType;
private:

	COGTransform * mTransform;
	COGBoxShape* mBoxShape;
	COGCircleShape* mCircleShape;
	COGLineShape* mLineShape;



	bool mGenerateCollisionEvents;
	std::vector<IPhysicsCollisionEvent*> mCollisionEventListeners;

};
