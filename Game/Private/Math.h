#pragma once

#include<cmath>

struct Vector2
{
	float x;
	float y;

	inline void Normalize()
	{
		float mag = std::sqrt((x * x) + (y * y));

		x /= mag;
		y /= mag;
	}

};

