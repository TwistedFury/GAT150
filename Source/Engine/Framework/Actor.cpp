#pragma once
#include "Actor.h"
#include "Renderer/Renderer.h"

namespace swaws
{
	/// <summary>
	/// Updates the actor's position and velocity based on the elapsed time and damping.
	/// </summary>
	/// <param name="dt">The elapsed time since the last update, in seconds.</param>
	void Actor::Update(float dt)
	{
		if (destroyed) return;

		if (lifespan != 0)
		{
			lifespan -= dt;
			destroyed = lifespan <= 0;
		}

		// Larger effect on damping speed with std::exp
		transform.position += velocity * dt;
		velocity *= std::exp(-damping * dt);
	}

	/// <summary>
	/// Draws the actor using the specified renderer.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the actor.</param>
	void Actor::Draw(Renderer& renderer)
	{
		if (destroyed) return;
		renderer.DrawTexture(m_texture.get(), transform.position.x, transform.position.y, transform.rotation, transform.scale);
	}

	/// <summary>
	/// Returns the effective radius of the actor based on its texture size, scale, and a scaling factor.
	/// </summary>
	/// <returns>The computed radius of the actor. Returns 0 if the actor has no texture.</returns>
	float Actor::GetRadius()
	{
		return (m_texture) ? (m_texture->GetSize().Length() * 0.5f) * transform.scale * 0.9f : 0;
	}
}
