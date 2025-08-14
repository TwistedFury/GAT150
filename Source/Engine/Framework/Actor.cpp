#pragma once
#include "Renderer/Renderer.h"
#include "Components/RendererComponent.h"

namespace swaws
{
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

	/// <summary>
	/// Draws the actor using the specified renderer.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the actor.</param>
	void Actor::Draw(Renderer& renderer)
	{
		if (destroyed) return;
		for (auto& component : m_components)
		{
			if (component->isActive)
			{
				auto rendererC = dynamic_cast<RendererComponent*>(component.get());
				if (rendererC) rendererC->Draw(renderer);
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


	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		// REMNANT MOMENT
		component->owner = this;
		m_components.push_back(std::move(component));
	}
}
