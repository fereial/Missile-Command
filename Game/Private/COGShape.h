#pragma once
#include "Game/Private/Component.h"
#include "Game/Engine\Public\EngineInterface.h"
#include "Game/Engine\Public\EngineTypes.h"
class COGShape : public Component
{
public:

	static std::vector<COGShape*> mShapeComponents;

public:

	COGShape(GameObject* pGO);
	~COGShape() = default;
	virtual void Initialize() override;

	virtual void Destroy() override;

	virtual void Render() = 0;

private:

	// TODO - add a color variable here!
	
};
