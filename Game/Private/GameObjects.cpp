#include "GameObjects.h"



GameObjects::GameObjects()
{
}


GameObjects::~GameObjects()
{
	for (Component* pComponent : mComponents)
	{
		pComponent->Destroy();

		delete pComponent;
	}
}

void GameObjects::AddComponent(Component * pComponent)
{
	mComponents.push_back(pComponent);
}

void GameObjects::Initialize() 
{
	for (Component* pComponent : mComponents)
	{
		pComponent->Initialize();
	}
}