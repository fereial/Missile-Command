#include "GameObject.h"
#include "Component.h"



GameObject::GameObject(Hash hash, GameObjectInventory* Inv)
	:mHash(hash),	
	gGameObjectInventory(Inv)
{
	gGameObjectInventory->Register(this);
}
void GameObject::AddComponent(Component* pComponent)
{
	mComponents.push_back(pComponent);
}


GameObject::~GameObject()
{
	for (Component* pComponent : mComponents)
	{
		pComponent->Destroy();

		delete pComponent;
	}
	gGameObjectInventory->Unregister(this);
}

void GameObject::Initialize()
{
	for (Component* pComponent : mComponents)
	{
		pComponent->Initialize();
	}
}


GameObjectHandle GameObject::GetHandle()
{
	GameObjectHandle temp;
	temp.mHash = mHash;

	return temp;
}
