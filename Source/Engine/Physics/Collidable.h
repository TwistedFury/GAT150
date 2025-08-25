#pragma once

namespace swaws
{
	class Collidable
	{
	public:
		virtual ~Collidable() = default;

		virtual void OnCollision(class Actor* other) = 0;
	};
}