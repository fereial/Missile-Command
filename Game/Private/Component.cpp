#include "Component.h"

Component::Component(GameObject* pGO)
	: mGO(pGO)
{
}

void Component::Initialize() { }
void Component::Destroy() { }


