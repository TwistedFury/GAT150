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

		bool destroyed{ false };
		float lifespan{ 0 };

		Transform transform;
		class Scene* scene{ nullptr };
	public:
		Actor() = default;
		Actor(const Transform& transform) :
			transform{ transform }
		{ }

		void Read(const json::value_t& value) override;

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		/// <summary>
		/// Returns a reference to the object's transform. This function is depracated.
		/// </summary>
		/// <returns>A reference to the transform associated with the object.</returns>
		Transform& GetTransform() { return transform; }

		/// <summary>
		/// Retrieves the radius value. Currently only in use for straight line detection in Scene.cpp
		/// </summary>
		/// <returns>The radius as a floating-point value.</returns>
		virtual float GetRadius();

		virtual void OnCollision(Actor* other) {}

		// Components
		void AddComponent(std::unique_ptr<Component> component);

		template <typename T>
		T* GetComponent();

		template <typename T>
		std::vector<T*> GetComponents();

	protected:
		std::vector<std::unique_ptr<Component>> m_components;
	};

	/// <summary>
	/// Retrieves the first component of the specified type from the actor.
	/// </summary>
	/// <typeparam name="T">The type of component to retrieve.</typeparam>
	/// <returns>A pointer to the first component of type T if found; otherwise, nullptr.</returns>
	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : m_components)
		{
			auto typeConvert = dynamic_cast<T*>(component.get());
			if (typeConvert) return typeConvert;
		}
		return nullptr;
	}

	/// <summary>
	/// Retrieves all components of the specified type attached to the actor.
	/// </summary>
	/// <typeparam name="T">The type of component to retrieve.</typeparam>
	/// <returns>A vector containing pointers to all components of type T attached to the actor.</returns>
	template<typename T>
	inline std::vector<T*> Actor::GetComponents()
	{
		std::vector<T*> results;
		for (auto& component : m_components)
		{
			auto typeConvert = dynamic_cast<T*>(component.get());
			if (typeConvert) results.push_back(typeConvert);
		}
		return results;
	}
}