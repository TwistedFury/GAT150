#pragma once
#include "Framework/Component.h"

namespace swaws 
{
	class ColliderComponent : public Component
	{
	public:
		virtual bool CheckCollision(ColliderComponent& other) = 0;
	};
}