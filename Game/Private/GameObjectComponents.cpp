// ConsoleApplication10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <algorithm>

//
// here's a very simple framework for a component based game object system
// it's all in one file so it's easier to share with you, but please split into a sensible file structure
//
// ideas on what to add next:
// * check the TODO's I left
// * you'll need add a COG to read in user input to adjust the velocity of the paddle
//

class GameObject;

struct Vector2
{
	float x;
	float y;
};

// all the different types of components
enum class ComponentType : int
{
	Transform = 0,
	Physics,
	BoxShape,
	CircleShape,
	Bounce
};

// our base component class
class Component
{
public:

	Component( GameObject* pGO )
		: mGO( pGO )
	{
	}

	virtual ComponentType GetType() const = 0;

	virtual void Initialize() { }
	virtual void Destroy() { }

protected:

	template<class T>
	void AddToComponentVector( std::vector<T*>& componentVector )
	{
		componentVector.push_back( (T*)this );
	}

	template<class T>
	void RemoveFromComponentVector( std::vector<T*>& componentVector )
	{
		componentVector.erase( std::remove( componentVector.begin(), componentVector.end(), this ), componentVector.end() );
	}

protected:

	GameObject* mGO;

};

// our game object, it's just a collection of components - that's it!
class GameObject
{
public:

	GameObject()
	{
	}

	~GameObject()
	{
		for ( Component* pComponent : mComponents )
		{
			pComponent->Destroy();

			delete pComponent;
		}
	}

	void Initialize()
	{
		for ( Component* pComponent : mComponents )
		{
			pComponent->Initialize();
		}
	}

	void AddComponent( Component* pComponent )
	{
		mComponents.push_back( pComponent );
	}

	template<class T>
	T* FindComponent( ComponentType eType )
	{
		for ( Component* pComponent : mComponents )
		{
			if ( pComponent->GetType() == eType )
			{
				return (T*)pComponent;
			}
		}

		return nullptr;
	}

private:
	std::vector<Component*> mComponents;

};

// COGTransform - where we are in space
class COGTransform : public Component
{
public:

	COGTransform( GameObject* pGO )
		: Component( pGO )
	{
	}

	virtual ComponentType GetType() const { return ComponentType::Transform; }

	Vector2& GetPosition() { return mPosition; }

private:

	Vector2 mPosition;

};

// COGShape - our baseclass for shapes
class COGShape : public Component
{
public:

	static std::vector<COGShape*> mShapeComponents;

public:

	COGShape( GameObject* pGO )
		: Component( pGO )
	{
	}

	virtual void Initialize() override
	{
		AddToComponentVector( mShapeComponents );
	}

	virtual void Destroy() override
	{
		RemoveFromComponentVector( mShapeComponents );
	}

	virtual void Render() = 0;

private:

	// TODO - add a color variable here!

};

std::vector<COGShape*> COGShape::mShapeComponents;

// COGBoxShape - box
class COGBoxShape : public COGShape
{
public:

	COGBoxShape( GameObject* pGO, float fWidth, float fHeight )
		: COGShape( pGO )
		, mWidth( fWidth )
		, mHeight( fHeight )
	{
	}

	virtual ComponentType GetType() const { return ComponentType::BoxShape; }

	virtual void Render() override
	{
		// tell EngineX to draw me
	}

private:

	float mWidth;
	float mHeight;

};

// COGCircleShape - box
class COGCircleShape : public COGShape
{
public:

	COGCircleShape( GameObject* pGO, float fRadius )
		: COGShape( pGO )
		, mRadius( fRadius )
	{
	}

	virtual ComponentType GetType() const { return ComponentType::CircleShape; }

	virtual void Render() override
	{
		// tell EngineX to draw me
	}

private:

	float mRadius;

};

// our interface that allows COGPhysics to talk to anyone
class COGPhysics;

class IPhysicsCollisionEvent
{
public:

	virtual void OnCollision( COGPhysics* pMe, COGPhysics* pOther ) = 0;

};

// COGPhysics - lets move around
class COGPhysics : public Component
{
public:

	static std::vector<COGPhysics*> mPhysicsComponents;

public:

	COGPhysics( GameObject* pGO, bool bGenerateCollisionEvents )
		: Component( pGO )
		, mGenerateCollisionEvents( bGenerateCollisionEvents )
	{
	}

	virtual ComponentType GetType() const { return ComponentType::Physics; }

	virtual void Initialize() override
	{
		mTransform = mGO->FindComponent<COGTransform>( ComponentType::Transform );
		mBoxShape = mGO->FindComponent<COGBoxShape>( ComponentType::BoxShape );
		mCircleShape = mGO->FindComponent<COGCircleShape>( ComponentType::CircleShape );

		AddToComponentVector( mPhysicsComponents );
	}

	virtual void Destroy() override
	{
		RemoveFromComponentVector( mPhysicsComponents );
	}

	virtual void Update( float fDeltaT )
	{
		// integrate velocity
		Vector2& myPosition = mTransform->GetPosition();

		myPosition.x += mVelocity.x * fDeltaT;
		myPosition.y += mVelocity.y * fDeltaT;

		// check collisions
		if ( mGenerateCollisionEvents )
		{
			for ( COGPhysics* pPhysicsOther : COGPhysics::mPhysicsComponents )
			{
				// do not collide with self
				if ( pPhysicsOther == this )
				{
					continue;
				}

				// TODO - maybe have IsColliding produce a vector/struct that contains the normal and then pass that into OnCollision?
				const bool bResult = IsColliding( pPhysicsOther );

				if ( bResult )
				{
					for ( IPhysicsCollisionEvent* pCollisionEventListener : mCollisionEventListeners )
					{
						pCollisionEventListener->OnCollision( this, pPhysicsOther );
					}
				}
			}
		}
	}

	bool IsColliding( COGPhysics* pOther )
	{
		if ( mCircleShape != nullptr && pOther->mBoxShape != nullptr )
		{
			// check a circle colliding with a box
		}

		// we don't cover the other cases
		// maybe assert here?

		return false;
	}

private:

	COGTransform* mTransform;
	COGBoxShape* mBoxShape;
	COGCircleShape* mCircleShape;

	Vector2 mVelocity;

	bool mGenerateCollisionEvents;
	std::vector<IPhysicsCollisionEvent*> mCollisionEventListeners;

};

std::vector<COGPhysics*> COGPhysics::mPhysicsComponents;

// COGBounce - where we make the ball bounce
class COGBounce : public Component, public IPhysicsCollisionEvent
{
public:

	COGBounce( GameObject* pGO )
		: Component( pGO )
	{
	}

	virtual ComponentType GetType() const { return ComponentType::Bounce; }

	virtual void OnCollision( COGPhysics* pMe, COGPhysics* pOther ) override
	{
		// tell pMe to bounce by setting our velocity to a new amount
	}

};

// create our paddle
GameObject* CreatePaddle()
{
	const float fPaddleWidth = 15.0f;
	const float fPaddleHeight = 50.0f;

	GameObject* pPaddle = new GameObject();

	COGTransform* pTransform = new COGTransform( pPaddle );
	pPaddle->AddComponent( pTransform );

	COGBoxShape* pBoxShape = new COGBoxShape( pPaddle, fPaddleWidth, fPaddleHeight );
	pPaddle->AddComponent( pBoxShape );

	COGPhysics* pPhysics = new COGPhysics( pPaddle, false );
	pPaddle->AddComponent( pPhysics );

	pPaddle->Initialize();

	return pPaddle;
}

// create ball (notice how it will generate events)
GameObject* CreateBall()
{
	const float fBallRadius = 12.0f;

	GameObject* pBall = new GameObject();

	COGTransform* pTransform = new COGTransform( pBall );
	pBall->AddComponent( pTransform );

	COGCircleShape* pBoxShape = new COGCircleShape( pBall, fBallRadius );
	pBall->AddComponent( pBoxShape );

	COGPhysics* pPhysics = new COGPhysics( pBall, true );
	pBall->AddComponent( pPhysics );

	pBall->Initialize();

	return pBall;
}

// the world, it contains all of our game objects and defines the order of updates
class World
{
public:

	void Create()
	{
		mGameObjects.push_back( CreatePaddle() );
		mGameObjects.push_back( CreatePaddle() );
		mGameObjects.push_back( CreateBall() );
	}

	void Destroy()
	{
		for ( GameObject* pGameObject : mGameObjects )
		{
			delete pGameObject;
		}

		mGameObjects.clear();
	}

	void Update( float fDeltaT )
	{
		// run simulation first
		for ( COGPhysics* pPhysics : COGPhysics::mPhysicsComponents )
		{
			pPhysics->Update( fDeltaT );
		}

		// then render everything
		for ( COGShape* pShape : COGShape::mShapeComponents )
		{
			pShape->Render();
		}
	}

private:

	std::vector<GameObject*> mGameObjects;

};

// TEST CODE!
int main()
{
	World world;
	world.Create();

	// obviously pass in a real delta time ...
	world.Update( 0.01f );
	world.Update( 0.01f );
	world.Update( 0.01f );

	world.Destroy();

    return 0;
}

