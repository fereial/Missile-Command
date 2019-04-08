#pragma once 
#include "Game\Private\Component.h"
#include "Game\Private\COGPhysics.h"
#include "Game\Private\GameObject.h"
#include "Game\Private\Math.h"
#include "Game\Engine\Public\EngineInterface.h"
#include <vector>
class COGPhysics;
class COGScore : public Component 
{
public:
	static std::vector<COGScore*> mScore;
public:
	COGScore(GameObject*pGO, exEngineInterface* pEngine);
	~COGScore() = default;
	virtual ComponentType GetType() const;
	virtual void Initialize() override;
	void ScoreManager(exEngineInterface*pEngine);
	int Score;
	int p2Score;
	exEngineInterface* mEngine;
	COGTransform* pTransform;
	Vector2 myTransform;
	COGPhysics* mPhysics;
	Vector2 starVelocity;
private:
	exColor c;
	int mFontID;
};