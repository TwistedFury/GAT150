#pragma once
#include "Object.h"

namespace swaws
{
	class Component : public Object
	{
	public:
		class Actor* owner{ nullptr };
	public:
		Component() = default;

		virtual void Update(float dt) = 0;

		virtual void Start() {}
		virtual void Destroy() {}
	};
}