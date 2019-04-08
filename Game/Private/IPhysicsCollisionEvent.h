#pragma once

class COGPhysics;

// our interface that allows COGPhysics to talk to anyone


class IPhysicsCollisionEvent
{
public:

	virtual void OnCollision(COGPhysics* pMe, COGPhysics* pOther) = 0;

};