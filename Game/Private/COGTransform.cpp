#include "COGTransform.h"

COGTransform::COGTransform(GameObject* pGO, float posX, float posY)
	: Component(pGO)
	{
		mPosition.x = posX;
		mPosition.y = posY;
	}

	ComponentType COGTransform:: GetType() const 
	{ return ComponentType::Transform; }

	Vector2& COGTransform::GetPosition()
	{ return mPosition; }

	void COGTransform::SetPosition(Vector2 pos)
	{
		mPosition = pos;
	}

