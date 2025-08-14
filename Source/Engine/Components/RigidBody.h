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

		void Update(float dt) override;

	};
}