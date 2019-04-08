#include "COGCircleShape.h"
#include "GameObjectHandle.h"


	COGCircleShape::COGCircleShape(GameObject* pGO, float fRadius, exEngineInterface* pPlayEngine)
		: COGShape(pGO)
		, mRadius(fRadius)
		,mPlayEngine(pPlayEngine)
	{
		c.mColor[0] = 25;
		c.mColor[1] = 255;
		c.mColor[2] = 0;
		c.mColor[3] = 255;

	}

	COGCircleShape::~COGCircleShape()
	{
		Destroy();
	}

ComponentType COGCircleShape::GetType() const 
{ return ComponentType::CircleShape; }

void COGCircleShape::Render() 
{
	GameObjectHandle mHandle = mGO->GetHandle();
	
		mRadius +=0.5;
		COGTransform* pTransform = mGO->FindComponent<COGTransform>(ComponentType::Transform);
		Vector2& myTransform = pTransform->GetPosition();
		exVector2 mPosition;
		mPosition.x = myTransform.x;
		mPosition.y = myTransform.y;

		mPlayEngine->DrawCircle(mPosition, mRadius, c, 1);
		if (mRadius >= 25) 
		{
			delete mGO;
		}
	
		
}

void COGCircleShape::Destory()
{
	COGShape::Destroy();
}


	

