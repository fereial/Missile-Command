#pragma once
#include "Game/Private/Component.h"
#include "Game/Private/COGShape.h"
#include "Game\Private\COGTransform.h"
#include "Game\Private\GameObject.h"
#include "Game/Engine\Public\EngineInterface.h"
#include "Game/Engine\Public\EngineTypes.h"
#include "Math.h"
#include "Game\Private\InputManager.h"
#include "World.h"

// COGCircleShape - box
class COGCircleShape : public COGShape
{
public:

	COGCircleShape(GameObject* pGO, float fRadius, exEngineInterface* pPlayEngine);
	~COGCircleShape();

	virtual ComponentType GetType() const;

	virtual void Render() override;
	void Destory();
	float mRadius;
private:

	
	exColor c;
	exEngineInterface* mPlayEngine;

};
