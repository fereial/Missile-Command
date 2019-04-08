#include "COGPhysics.h"
#include "COGBoxShape.h"
#include "COGTransform.h"
#include "COGCircleShape.h"
#include "COGLineShape.h"
#include "COGMeteoriteController.h"


// COGPhysics - lets move around


    COGPhysics::COGPhysics(GameObject* pGO, bool bGenerateCollisionEvents, float vX ,float vY)
		: Component(pGO)
		, mGenerateCollisionEvents(bGenerateCollisionEvents)
	{
		mVelocity.x = vX;
		mVelocity.y = vY;
		collisionType = 0;
	}

	ComponentType COGPhysics::GetType() const { return ComponentType::Physics; }

	 void COGPhysics::Initialize() 
	{
		mTransform = mGO->FindComponent<COGTransform>(ComponentType::Transform);
		mBoxShape = mGO->FindComponent<COGBoxShape>(ComponentType::BoxShape);
		mCircleShape = mGO->FindComponent<COGCircleShape>(ComponentType::CircleShape);
		mLineShape = mGO->FindComponent<COGLineShape>(ComponentType::LineShape);
		
		AddToComponentVector(mPhysicsComponents);
	}

	void COGPhysics::Destroy() 
	{
		RemoveFromComponentVector(mPhysicsComponents);
	}

	void COGPhysics::Update(float fDeltaT)
	{
		// integrate velocity
		Vector2& myPosition = mTransform->GetPosition();

		myPosition.x += mVelocity.x * fDeltaT;
		myPosition.y += mVelocity.y * fDeltaT;

		// check collisions
		if (mGenerateCollisionEvents)
		{
			for (COGPhysics* pPhysicsOther : COGPhysics::mPhysicsComponents)
			{
				// do not collide with self
				if (pPhysicsOther == this)
				{
					continue;
				}

				
				const bool bResult = IsColliding(pPhysicsOther);

				if (bResult)
				{
					for (IPhysicsCollisionEvent* pCollisionEventListener : mCollisionEventListeners)
					{
						pCollisionEventListener->OnCollision(this, pPhysicsOther);
					}
				}
			}
		}
	}


	bool COGPhysics::IsColliding(COGPhysics* pOther)
	{
		Vector2& myTransform = mTransform->GetPosition();
		if (mCircleShape != nullptr && pOther->mLineShape != nullptr) 
		{
			COGTransform* pLineTransform = pOther->mGO->FindComponent<COGTransform>(ComponentType::Transform);

			const float& CircleRadius = mCircleShape->mRadius;

			const Vector2& circlePosition = myTransform;
			const Vector2& lineEndPosition = pLineTransform->GetPosition();
			if (lineEndPosition.x  <= circlePosition.x + CircleRadius && lineEndPosition.x >= circlePosition.x - CircleRadius
				&& lineEndPosition.y  <= circlePosition.y + CircleRadius && lineEndPosition.y >= circlePosition.y - CircleRadius) 
			{
				pOther->mGO->~GameObject();
			}
			
		}
		if (mLineShape != nullptr && pOther->mBoxShape != nullptr)
		{
			COGTransform* pBoxTransform = pOther->mGO->FindComponent<COGTransform>(ComponentType::Transform);

			const float& W = pOther->mBoxShape->mWidth;
			const float& H = pOther->mBoxShape->mWidth;

			const Vector2& circlePosition = myTransform;
			const Vector2& lineEndPosition = pBoxTransform->GetPosition();
			if (lineEndPosition.x <= circlePosition.x + W/2   && lineEndPosition.x  >= circlePosition.x - W/2
				&& lineEndPosition.y <= circlePosition.y + H/2 && lineEndPosition.y >= circlePosition.y - H /2 && pOther->mBoxShape->type == 1)
			{
				pOther->mGO->~GameObject();
				mLineShape->Destroy();
			}

		}

		if (mBoxShape != nullptr && pOther->mLineShape != nullptr) 
		{
			COGTransform* pLineTransform = pOther->mGO->FindComponent<COGTransform>(ComponentType::Transform);
			const float& H = mBoxShape->mWidth;
			const Vector2& groundPosition = myTransform;
			if (groundPosition.y  < pLineTransform->GetPosition().y ) 
			{

				pOther->mLineShape->Destroy();
			}

		}


		return false;
	}
	void COGPhysics::AddCollisionEventListener(IPhysicsCollisionEvent* pEvent) 
	{
		mCollisionEventListeners.push_back(pEvent);
	}

	
	std::vector<COGPhysics*> COGPhysics::mPhysicsComponents;

