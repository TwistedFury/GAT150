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
}
