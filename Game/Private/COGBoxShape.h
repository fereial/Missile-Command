#pragma once
#include "Game/Private/Component.h"
#include "Game/Private/COGShape.h"
#include "Game/Engine\Public\EngineInterface.h"
#include "Game/Engine\Public\EngineTypes.h"
#include "GameObject.h"
#include "COGTransform.h"

// COGBoxShape - box
class COGBoxShape : public COGShape
{
public:

	COGBoxShape(GameObject* pGO, float fWidth, float fHeight, exEngineInterface* playEngine , int type);
	~COGBoxShape() = default;

	virtual ComponentType GetType() const;

	virtual void Render() override;
	float mWidth;
	float mHeight;
	int type;

private:

	
	exColor c;
	exEngineInterface* mPlayEngine;
};
