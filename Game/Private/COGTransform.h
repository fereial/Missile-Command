#pragma once
#include "Game/Private/Component.h"
#include "Game/Private/Math.h"

class COGTransform : public Component
{
public:

	COGTransform(GameObject* pGO,float posX, float posY);
	~COGTransform() = default;
	virtual ComponentType GetType() const;
	Vector2& GetPosition();
	void SetPosition(Vector2 pos);

private:

	Vector2 mPosition;

};
