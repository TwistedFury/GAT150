#pragma once

#include <box2d/box2d.h>

namespace swaws
{
	class PhysicsBody
	{
	public:
		enum class Shape
		{
			Box,
			Circle,
			Capsule
		};

		struct PhysicsBodyDef
		{
			// Body
			float gravityScale = 1; // < 0 = Reverse, 0 = None, > 0 = Normal, 1 = NormalMax
			float linearDamping = 0.2f; // How fast to slow down movement
			float angularDamping = 0.2f; // How fast to slow down rotation
			bool  constrainAngle = false; // Can the angle change (Can it rotate); false = yes, true = no
			bool  isDynamic = true; // Is this affected by Gravity?

			// Material
			float friction = 0.3f; // How much friction does this object have? Less -> Ice, More -> Rug
			float restitution = 0.5f; // How much can this object bounce? 1 = Forever, 0 = Never
			float density = 1.0f; // Relating to mass. Less -> Styrofoam, More -> Steel

			// Shape
			Shape shape = Shape::Box; // What shape for Collision Check? Use Enum Class
			bool isSensor = false; // Is this a physical object (false)? If true -> Something like a checkpoint.. trigger

			class Actor* actor{ nullptr }; // Who is this attached to?
		};

		PhysicsBody(const Transform& transform, const vec2& size, const PhysicsBodyDef& def, const class Physics& physics);
		~PhysicsBody();

		vec2 GetPosition();
		float GetAngle();

		void ApplyForce(const vec2& force);
		void ApplyTorque(float torque); // torque is in radians

		void SetVelocity(const vec2& v);
	private:
		b2BodyId m_bodyId{ b2_nullBodyId };
	};
}