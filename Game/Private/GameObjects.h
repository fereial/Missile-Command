#pragma once
#include "Game\Private\Component.h"
#include <vector>
class GameObjects
{
public:

	GameObjects();

	~GameObjects();

	void Initialize();
	

	void AddComponent(Component* pComponent);

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

private:
	std::vector<Component*> mComponents;

};