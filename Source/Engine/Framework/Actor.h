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
		// std::string name; // REMOVED: duplicate (shadowed Object::name)
		std::string tag;

		float speed = 200;
		float maxSpeed = 1000;
		float lifespan{ 0 };

		bool destroyed{ false };
		bool persistent{ false };

		Transform transform;
		class Scene* scene{ nullptr };

	public:
		Actor() = default;
		Actor(const Transform& transform) :
			transform{ transform }
		{ }

		Actor(const Actor& other);

		CLASS_PROTOTYPE(Actor)

		void Read(const json::value_t& value) override;
		virtual void Start();
		virtual void Destroy();
		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		Transform& GetTransform() { return transform; }
		virtual float GetRadius();
		virtual void OnCollision(Actor* other);

		void AddComponent(std::unique_ptr<Component> component);

		template <typename T>
		T* GetComponent();

		template <typename T>
		std::vector<T*> GetComponents();

		bool GetObjectIsActive() { return isActive; }

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
			if (!component) continue;
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