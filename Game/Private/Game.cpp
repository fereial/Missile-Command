//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.cpp
// implementation of MyGame, an implementation of exGameInterface
//

#include "Game/Private/Game.h"

#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"
#include "Game\Private\World.h"
#include "Game\Private\GameObject.h"
#include "Game/Private/COGPlayercontroller.h"
#include "Game\Private\InputManager.h";

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* gWindowName = "Sample EngineX Game - PONG GAME";
const int GameScreenWidth = 800;
const int GameScreenHeight = 600;
World* world = nullptr;
InputManager* inpoutManager = nullptr;




//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()
	: mEngine( nullptr )
	, mFontID( -1 )
	, mUp( false )
	, mDown( false )
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::~MyGame()
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Initialize( exEngineInterface* pEngine )
{
	mEngine = pEngine;

	mFontID = mEngine->LoadFont("04B_08.ttf", 32);

	mScoreP1.x = 280.0f;
	mScoreP1.y = 20.0f;

	mScoreP2.x = 450.0f;
	mScoreP2.y = 20.0f;
	// world = new World(pEngine);	
	World::getinstance()->Create(pEngine);
	InputManager::getinstance();
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* MyGame::GetWindowName() const
{
	return gWindowName;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::GetClearColor( exColor& color ) const
{
	color.mColor[0] = 128;
	color.mColor[1] = 128;
	color.mColor[2] = 128;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEvent( SDL_Event* pEvent )
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEventsConsumed()
{
	/*int nKeys = 0;
	const Uint8 *pState = SDL_GetKeyboardState( &nKeys );

	mUp = pState[SDL_SCANCODE_UP];
	mDown = pState[SDL_SCANCODE_DOWN];

	mW = pState[SDL_SCANCODE_W];
	mS = pState[SDL_SCANCODE_S];*/
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Run( float fDeltaT )
{
	world->Update(fDeltaT);	
}
