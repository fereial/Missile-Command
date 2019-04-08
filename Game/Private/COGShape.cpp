#include "COGShape.h"


     COGShape::COGShape(GameObject* pGO)
		: Component(pGO)
	{
	}

	 void COGShape::Initialize() 
	{
		AddToComponentVector(mShapeComponents);
	}

	 void COGShape::Destroy() 
	{
		RemoveFromComponentVector(mShapeComponents);
	}

	 std::vector<COGShape*> COGShape::mShapeComponents;

