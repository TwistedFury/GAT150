#pragma once

#include "Core/Serializable.h"
#include "Vector2.h"

namespace swaws
{
	struct Transform : public Serializable
	{
		vec2 position{ 0, 0 };
		float rotation = 0, scale = 1.0f;

		Transform() = default;
		Transform(const vec2& pos, float rot = 0, float sca = 1.0f) :
			position{ pos }, rotation{ rot }, scale{ sca } { }

		void Read(const json::value_t& value) override;

	};
}