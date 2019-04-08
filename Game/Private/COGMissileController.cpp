#include "COGMissileController.h"
#include "World.h"


COGMissileController::COGMissileController(GameObject* pGO)
	: Component(pGO)
{
	refFinalPos.x = 0;
	refFinalPos.y = 0;
}

void COGMissileController::Initialize()
{
	AddToComponentVector(mMissileController);
	mTransfrom = mGO->FindComponent<COGTransform>(ComponentType::Transform);
	mLineShape = mGO->FindComponent<COGLineShape>(ComponentType::LineShape);
	mPhysics = mGO->FindComponent<COGPhysics>(ComponentType::Physics);
	mPhysics->mVelocity.x = 0;
	mPhysics->mVelocity.y = 0;
}

void COGMissileController::Destroy()
{
	RemoveFromComponentVector(mMissileController);
}

Vector2 COGMissileController::Direction(Vector2 finalPos, Vector2 initPos)
{	
	Vector2 heading;
	heading.x = initPos.x - finalPos.x;
	heading.y = initPos.y - finalPos.y;
	heading.Normalize();
	mPhysics->mVelocity.x = heading.x * -75;
	mPhysics->mVelocity.y = heading.y * -75;
	mTransfrom->SetPosition(initPos);
	mLineShape->Update(initPos,finalPos);

	
	return heading;
}




void COGMissileController::Update()
{
	Vector2& nowPosition = mTransfrom->GetPosition();
	if (nowPosition.y < refFinalPos.y)
	{
		GameObject* Bang = World::getinstance()->SpawnBang(nowPosition.x, nowPosition.y);
		delete mGO;
	}
}

void COGMissileController::SpawnMissle(Vector2 initialPosition, Vector2 finalPos)
{
	Direction(finalPos, initialPosition);
	refFinalPos.x = finalPos.x;
	refFinalPos.y = finalPos.y;
	
}


ComponentType COGMissileController::GetType() const
{
	return ComponentType::MissileController;
}
std::vector<COGMissileController*> COGMissileController::mMissileController;