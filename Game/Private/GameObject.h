#pragma once
#include <iostream>
#include "Game/Private/ComponentType.h"
#include "Game\Private\Component.h"
#include <functional>
#include "Game/Engine/Public/EngineTypes.h"
#include "Game/Engine/Public/EngineInterface.h"
#include <vector>
#include <algorithm>
#include "Game\Private\HashMap.h"
#include "GameObjectHandle.h"
#include "GameObjectInventory.h"

class Component;
enum class ComponentType;
// our game object, it's just a collection of components - that's it!
class GameObject
{
public:
	Hash mHash;
public:

	GameObject(Hash hash, GameObjectInventory* Inv);
	~GameObject();

	void AddComponent(Component* pComponent);
	GameObjectHandle GetHandle();

	void Initialize();


	template<class T>
	T* FindComponent(ComponentType eType)
	{
		for (Component* pComponent : mComponents)
		{
			if (pComponent->GetType() == eType)
			{
				return (T*)pComponent;
			}
		}

		return nullptr;
	}

	//Hold the games two colors so that all objects can aces them


private:
	std::vector<Component*> mComponents;
	GameObjectInventory* gGameObjectInventory;

};
