#include "COGScore.h"

#include "COGPhysics.h"

#include <string>

COGScore::COGScore(GameObject *pGO, exEngineInterface*pEngine)
	:Component(pGO)
	,mEngine(pEngine)
{
	Score = 0;
	p2Score = 0;
	c.mColor[0] = 25;
	c.mColor[1] = 255;
	c.mColor[2] = 0;
	c.mColor[3] = 255;
	mFontID = mEngine->LoadFont("04B_24.ttf", 32);
}

ComponentType COGScore::GetType() const
{
	return ComponentType::Score;
}

void COGScore::Initialize()
{
	pTransform = mGO->FindComponent<COGTransform>(ComponentType::Transform);
	mPhysics = mGO->FindComponent<COGPhysics>(ComponentType::Physics);
	starVelocity = mPhysics->mVelocity;
	AddToComponentVector(mScore);
	
}

void COGScore::ScoreManager(exEngineInterface* playEngine)
{
	Vector2& myTransform = pTransform->GetPosition();
	if (myTransform.x < 0) 
	{
		++p2Score;
		myTransform.x = 400;
		myTransform.y = 300;
		mPhysics->mVelocity = starVelocity;
		mPhysics->mVelocity.x *= -1.0f;
		
	}
	else if (myTransform.x > 800) 
	{
		++Score;
		myTransform.x = 400;
		myTransform.y = 300;
		mPhysics->mVelocity = starVelocity;
		mPhysics->mVelocity.x *= 1.0f;
	}
	exVector2 mScore1;
	exVector2 mScore2;


	mScore1.x = 280.0f;
	mScore1.y = 20.0f;

	mScore2.x = 450.0f;
	mScore2.y = 20.0f;

	std::string tempA = std::to_string(Score);
	std::string tempB = std::to_string(p2Score);

	const char* ScoreP1 = tempA.c_str();
	const char* ScoreP2 = tempB.c_str();
	playEngine->DrawText(mFontID, mScore1, ScoreP1, c, 1);
	playEngine->DrawText(mFontID, mScore2, ScoreP2, c, 1);
	
}
std::vector<COGScore*> COGScore::mScore;