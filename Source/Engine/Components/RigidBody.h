#pragma once
#include "Framework/Component.h"

namespace swaws
{
	class RigidBody : public Component
	{
		// Variables
	public:
		PhysicsBody::PhysicsBodyDef bodyDef{ 0 };
		vec2 size{ 0, 0 };

		vec2 velocity{ 0, 0 };
		float damping{ 0 };

		// Methods
	public:
		RigidBody() = default;
		RigidBody(const RigidBody& other);

		CLASS_PROTOTYPE(RigidBody)

		void Start() override;
		void Update(float dt) override;
		void Read(const json::value_t& value) override;

		void ApplyForce(const vec2& force);
		void ApplyTorque(float torque); // torque is in radians
		void SetVelocity(const vec2& v);

        PhysicsBody* GetBody() { return m_body.get(); }
	private:
		std::unique_ptr<PhysicsBody> m_body{ nullptr };
	};
}