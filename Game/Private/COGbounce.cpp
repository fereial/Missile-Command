#include "COGBounce.h"


	COGBounce::COGBounce(GameObject* pGO)
		: Component(pGO)
	{
	}

	 ComponentType COGBounce::GetType() const { return ComponentType::Bounce; }
	 void COGBounce::Initialize() 
	 {
		 COGPhysics* pPhysics = mGO->FindComponent<COGPhysics>(ComponentType::Physics);
		 COGTransform* pTransform = mGO->FindComponent<COGTransform>(ComponentType::Transform);
		 
		 /*Velocity = mPhysics.mVelocity;*/
		 // add myself to the list of objects that are interested in collisions
		 // COGPhysics is able to interface with us because we inherit from IPhysicsCollisionEvent
		 pPhysics->AddCollisionEventListener(this);
	 }

	 void COGBounce::OnCollision(COGPhysics* pMe, COGPhysics* pOther) 
	 {
		 if (pMe->collisionType == 0) 
		 {
			 if (pMe->mVelocity.x < 320.0f) 
			 {
				pMe->mVelocity.x *=- 1.2;
			 }
			 else
			 {
				 pMe->mVelocity.x *= -1;
			 }
		 }
		 else if (pMe->collisionType == 1) 
		 {
			 pMe->mVelocity.y*=-1;
		 }
		
 	 };


	
	

