#include "RigidBody.h"

namespace swaws
{
	FACTORY_REGISTER(RigidBody)

	void RigidBody::Update(float dt)
	{
		// Larger effect on damping speed with std::exp
		owner->transform.position += velocity * dt;
		velocity *= std::exp(-damping * dt);
	}

	void RigidBody::Read(const json::value_t& value)
	{
		Object::Read(value);
		JSON_READ(value, velocity);
		JSON_READ(value, damping);
	}
}
