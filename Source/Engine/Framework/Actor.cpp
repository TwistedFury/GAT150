#pragma once
#include "Renderer/Renderer.h"
#include "Components/RendererComponent.h"
#include "Actor.h"

namespace swaws
{
	FACTORY_REGISTER(Actor)

	/// <summary>
	/// Updates the actor's position and velocity based on the elapsed time and damping.
	/// </summary>
	/// <param name="dt">The elapsed time since the last update, in seconds.</param>
	void Actor::Update(float dt)
	{
		if (lifespan > 0)
		{
			lifespan -= dt;
			destroyed = lifespan <= 0;
		}

		if (destroyed) return;

		// Update Components
		for (auto& component : m_components)
		{
			if (component->isActive) component->Update(dt);
		}
	}

	void Actor::Start()
	{
		// Start components
		for (auto& component : m_components)
		{
			component->Start();
		}
	}

	void Actor::Destroy()
	{
		// Destroy components
		for (auto& component : m_components)
		{
			component->Destroy();
		}
	}

	/// <summary>
	/// Draws the actor using the specified renderer.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the actor.</param>
	void Actor::Draw(Renderer& renderer)
	{
		if (destroyed) return;

		for (auto& component : m_components)
		{
			if (!component) // new guard
			{
				Logger::Error("Null component in Actor '{}' during Draw", name);
				continue;
			}
			if (!component->isActive) continue;

			// Optional vptr sanity (debug only)
#ifndef NDEBUG
			if (reinterpret_cast<void**>(component.get())[0] == nullptr)
			{
				Logger::Error("Corrupted component (vptr null) in Actor '{}'", name);
				continue;
			}
#endif
			if (auto rendererC = dynamic_cast<RendererComponent*>(component.get()))
			{
				rendererC->Draw(renderer);
			}
		}
	}

	/// <summary>
	/// Returns the effective radius of the actor based on its texture size, scale, and a scaling factor.
	/// </summary>
	/// <returns>The computed radius of the actor. Returns 0 if the actor has no texture.</returns>
	float Actor::GetRadius()
	{
		return 50.0f; // (m_texture) ? (m_texture->GetSize().Length() * 0.5f) * transform.scale * 0.9f : 0;
	}

	void Actor::OnCollision(Actor* other)
	{
		auto collidables = GetComponents<Collidable>();
		for (auto& collidable : collidables) collidable->OnCollision(other);
	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		// REMNANT MOMENT
		if (!component)
		{
			Logger::Error("Attempted to add null Component to Actor '{}'", name);
			return;
		}
		component->owner = this;
		m_components.push_back(std::move(component));
	}

	Actor::Actor(const Actor& other) :
		Object{ other },
		tag{ other.tag },
		speed{ other.speed },
		maxSpeed{ other.maxSpeed },
		lifespan{ other.lifespan },
		destroyed{ other.destroyed },
		persistent{ other.persistent },
		transform{ other.transform }
	{
		for (auto& component : other.m_components)
		{
			auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			AddComponent(std::move(clone)); // sets owner
		}
	}

	void Actor::Read(const json::value_t& value)
	{
		Object::Read(value);
		JSON_READ(value, tag);
		JSON_READ(value, lifespan);
		JSON_READ(value, persistent);
		if (JSON_HAS(value, transform)) transform.Read(JSON_GET(value, transform));

		if (JSON_HAS(value, components))
		{
			for (auto& compVal : JSON_GET(value, components).GetArray())
			{
				std::string type;
				JSON_READ(compVal, type);
				auto component = Factory::Instance().Create<Component>(type);
				if (!component)
				{
					Logger::Error("Failed to create Component '{}' for Actor '{}'", type, name);
					continue;
				}
				component->Read(compVal);
				AddComponent(std::move(component));
			}
		}
		else Logger::Error("Actor '{}' missing 'components'", name);
	}
}
