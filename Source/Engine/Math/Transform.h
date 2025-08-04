#pragma once

#include "Vector2.h"

namespace swaws
{
	struct Transform
	{
		vec2 position{ 0, 0 };
		float rotation = 0, scale = 1.0f;

		Transform() = default;
		Transform(const vec2& pos, float rot = 0, float sca = 1.0f) :
			position{ pos }, rotation{ rot }, scale{ sca } { }


	};
}