#include "COGMeteoriteController.h"
#include "World.h"

COGMeteoriteController::COGMeteoriteController(GameObject * pGO)
	:Component(pGO)
{
}

void COGMeteoriteController::Initialize()
{
	AddToComponentVector(mMeteoriteController);
	mTransfrom = mGO->FindComponent<COGTransform>(ComponentType::Transform);
	mLineShape = mGO->FindComponent<COGLineShape>(ComponentType::LineShape);
	mPhysics = mGO->FindComponent<COGPhysics>(ComponentType::Physics);
	mPhysics->mVelocity.x = 0;
	mPhysics->mVelocity.y = 0;

}

void COGMeteoriteController::Destroy()
{
}

void COGMeteoriteController::SpawnMissle()
{	
	Direction();
}

void COGMeteoriteController::Update()
{
	
}

Vector2 COGMeteoriteController::Direction()
{
	Vector2 heading;
	Vector2 finalPos;
	Vector2 initPos;
	int rndX = (rand() % 800);
	if (rndX <= 400) 
	{	
		int rndf = (rand() % 350);
		initPos.x = rndX;
		initPos.y = 0;
		finalPos.x = rndf;
		finalPos.y = 600;
	}
	else if (rndX >=400) 
	{
		int rndf = (rand() % 550) + 450;
		finalPos.x = rndf;
		finalPos.y = 600;
		initPos.x = rndX;
		initPos.y = 0;
	}
	heading.x =  finalPos.x - initPos.x;
	heading.y = finalPos.y - initPos.y;
	heading.Normalize();
	mPhysics->mVelocity.x = heading.x * 20;
	mPhysics->mVelocity.y = heading.y * 20;
	mTransfrom->SetPosition(initPos);
	mLineShape->Update(initPos, finalPos); 


	return heading;
}

ComponentType COGMeteoriteController::GetType() const
{
	return ComponentType::MeteoriteController;
}
std::vector<COGMeteoriteController*> COGMeteoriteController::mMeteoriteController;