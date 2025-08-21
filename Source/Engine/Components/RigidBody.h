#pragma once
#include "Framework/Component.h"

namespace swaws
{
	class RigidBody : public Component
	{
		// Variables
	public:
		vec2 velocity{ 0, 0 };
		float damping{ 0 };

		// Methods
	public:
		CLASS_PROTOTYPE(RigidBody)

		void Update(float dt) override;
		void Read(const json::value_t& value) override;
	};
}