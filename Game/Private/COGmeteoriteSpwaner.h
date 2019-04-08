#pragma once
#include "Game\Private\Component.h"
#include "Game\Private\Math.h"
#include "Game\Engine\Public\EngineInterface.h"
#include "Game\Engine\Public\EngineTypes.h"
class COGTransform;
class COGMissileController;

class COMeteoriteSpawner : public Component
{
public:
	COMeteoriteSpawner(GameObject* pGO, exEngineInterface* mPlayEngine);
	~COMeteoriteSpawner() = default;
	void Initialize();
	void Destroy();
	void Update(float fDelta);
	static std::vector<COMeteoriteSpawner*> mMeteoriteSpawner;
	virtual ComponentType GetType() const;
	Vector2 mousePos;
private:
	float timer;
	exEngineInterface * mPlayEngine;
	COGTransform * mTransfrom;
};