#include "COGBoxShape.h"


COGBoxShape::COGBoxShape(GameObject* pGO, float fWidth, float fHeight, exEngineInterface* playEngine, int type )
	: COGShape(pGO)
	, mWidth(fWidth)
	, mHeight(fHeight)
	,type(type)
	,mPlayEngine(playEngine)
	{
		c.mColor[0] = 255;
		c.mColor[1] = 255;
		c.mColor[2] = 255;
		c.mColor[3] = 255;
	}

 ComponentType COGBoxShape::GetType() const 
 { return ComponentType::BoxShape; }

void COGBoxShape::Render() 
{
	COGTransform* pTransform = mGO->FindComponent<COGTransform>(ComponentType::Transform);

	Vector2& myTransform = pTransform->GetPosition();

	exVector2 topLeft;
	exVector2 botRight;	
	topLeft.x = myTransform.x - (mWidth / 2);
	topLeft.y = myTransform.y - (mHeight / 2);
	botRight.x = myTransform.x + (mWidth / 2);
	botRight.y = myTransform.y + (mHeight / 2);
	mPlayEngine->DrawBox(topLeft, botRight, c, 1);
}


