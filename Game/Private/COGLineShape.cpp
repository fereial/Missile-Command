#include "COGLineShape.h"


COGLineShape::COGLineShape(GameObject * pGO, exEngineInterface * pPlayEngine)
	: COGShape(pGO)
	, mPlayEngine(pPlayEngine)
{
	c.mColor[0] = 25;
	c.mColor[1] = 255;
	c.mColor[2] = 255;
	c.mColor[3] = 255;
	mPositionOther.x = 0;
	mPositionOther.y = 0;
	finalPos.x = 0;
	finalPos.y =  0;
	makeBang = false;
	goBoom = false;
	
}

COGLineShape::~COGLineShape()
{
	Destroy();
}

void COGLineShape::Initialize()
{
	COGShape::Initialize();
	mHandle = mGO->GetHandle();
}

void COGLineShape::Destroy()
{
	COGShape::Destroy();
}
void COGLineShape::Render()
{
	
	
		COGTransform* pTransfrom = mGO->FindComponent<COGTransform>(ComponentType::Transform);
		Vector2 myPosition = pTransfrom->GetPosition();
		exVector2 posA;
		exVector2 posB;
		posA.x = myPosition.x;
		posA.y = myPosition.y;
		posB.x = mPositionOther.x;
		posB.y = mPositionOther.y;

		mPlayEngine->DrawLine(posA, posB, c, 1);
		
}


void COGLineShape::Update(Vector2 positionOther, Vector2 finalPos)
{

	mPositionOther.x = positionOther.x;
	mPositionOther.y = positionOther.y;
	finalPos.x = finalPos.x;
	finalPos.y = finalPos.y;
}

ComponentType COGLineShape::GetType() const
{
	return ComponentType::LineShape;
}


