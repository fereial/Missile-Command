// all the different types of components
#pragma once
enum class ComponentType : int
{
	Transform = 0,
	Physics,
	BoxShape,
	CircleShape,
	Bounce,
	PlayerController,
	Score,
	MissileController,
	LineShape,
	MeteoriteSpawner,
	MeteoriteController
};