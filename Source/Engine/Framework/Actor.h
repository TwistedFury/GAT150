#pragma once
#include "Object.h"
#include "Component.h"
#include "Math/Transform.h"
#include "Math/Vector3.h"
#include "Renderer/Texture.h"
#include <memory>
#include <string>
#include <vector>

namespace swaws
{
	class Actor : public Object
	{
	public:
		std::string name;
		std::string tag;

		float speed = 200;
		float maxSpeed = 200;

		vec2 velocity{ 0, 0 };
		float damping{ 0.3f };

		float length{ 0 }; // USED FOR STRAIGHT OBJECTS LIKE LASERS

		bool destroyed{ false };
		float lifespan{ 0 };

		Transform transform;
		class Scene* scene{ nullptr };
	public:
		Actor() = default;
		Actor(const Transform& transform) :
			transform{ transform }
		{ }

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		/// <summary>
		/// Returns a reference to the object's transform. This function is depracated.
		/// </summary>
		/// <returns>A reference to the transform associated with the object.</returns>
		Transform& GetTransform() { return transform; }
		virtual float GetRadius();

		virtual void OnCollision(Actor* other) = 0;

		// Components
		void AddComponent(std::unique_ptr<Component> component);

	protected:
		std::vector<std::unique_ptr<Component>> m_components;
	};
}