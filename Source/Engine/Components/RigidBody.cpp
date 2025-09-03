#include "RigidBody.h"

#include "SpriteRenderer.h"
#include "Engine.h"

namespace swaws
{
	FACTORY_REGISTER(RigidBody)

	RigidBody::RigidBody(const RigidBody& other) 
	{
		bodyDef = other.bodyDef;
		size = other.size;
	}

	void RigidBody::Start()
	{
		bodyDef.actor = owner;
		if (size.x == 0 && size.y == 0)
		{
			auto spriteRenderer = owner->GetComponent<SpriteRenderer>();
			if (spriteRenderer && spriteRenderer->texture)
			{
				size = spriteRenderer->texture->GetSize();
			}
			else
			{
				spriteRenderer->Start();
				size = spriteRenderer->texture->GetSize();
			}
		}
		m_body = std::make_unique<PhysicsBody>(owner->transform, size, bodyDef, GetEngine().GetPhysics());
	}

	void RigidBody::Update(float dt)
	{
		owner->transform.position = m_body->GetPosition();
		owner->transform.rotation = math::RadToDeg(m_body->GetAngle());
		velocity = m_body->GetVelocity();

		//// Larger effect on damping speed with std::exp
		//owner->transform.position += velocity * dt;
		//velocity *= std::exp(-damping * dt);
	}

	void RigidBody::Read(const json::value_t& value)
	{
		Object::Read(value);

		JSON_READ(value, size);
		//JSON_READ(value, scale);

		JSON_READ_NAME(value, "gravityScale", bodyDef.gravityScale);
		JSON_READ_NAME(value, "linearDamping", bodyDef.linearDamping);
		JSON_READ_NAME(value, "angularDamping", bodyDef.angularDamping);
		JSON_READ_NAME(value, "constrainAngle", bodyDef.constrainAngle);
		JSON_READ_NAME(value, "isDynamic", bodyDef.isDynamic);
		JSON_READ_NAME(value, "friction", bodyDef.friction);
		JSON_READ_NAME(value, "restitution", bodyDef.restitution);
		JSON_READ_NAME(value, "density", bodyDef.density);
		JSON_READ_NAME(value, "isSensor", bodyDef.isSensor);

		std::string shapeName;
		JSON_READ_NAME(value, "shape", shapeName);

		if (!shapeName.empty()) {
			if (compareIgnore(shapeName, "box")) bodyDef.shape = PhysicsBody::Shape::Box;
			else if (compareIgnore(shapeName, "capsule")) bodyDef.shape = PhysicsBody::Shape::Capsule;
			else if (compareIgnore(shapeName, "circle")) bodyDef.shape = PhysicsBody::Shape::Circle;
		}
	}

	void RigidBody::ApplyForce(const vec2& force)
	{
		m_body->ApplyForce(force);
	}

	void RigidBody::ApplyTorque(float torque)
	{
		m_body->ApplyTorque(torque);
	}

	void RigidBody::SetVelocity(const vec2& v)
	{
		m_body->SetVelocity(v);
	}
}
