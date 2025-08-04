#pragma once

#include "../Math/Transform.h"
#include "../Math/Vector3.h"
#include "../Renderer/Model.h"
#include <memory>
#include <string>

namespace swaws
{
	class Actor
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
		Actor(const Transform& transform, std::shared_ptr<class Model> model) :
		transform{ transform }, m_model{ model } 
		{ }

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		/// <summary>
		/// Returns a reference to the transform object. This method has deprecated.
		/// </summary>
		/// <returns>A reference to the internal Transform object.</returns>
		Transform& GetTransform() { return transform; }
		virtual float GetRadius();

		virtual void OnCollision(Actor* other) = 0;

		// colors
		void SetColor(vec3 color) { m_model->SetColor(color); }
		vec3 GetColor() const { return m_model->GetColor(); }

	protected:
		std::shared_ptr<Model> m_model;
	};
}