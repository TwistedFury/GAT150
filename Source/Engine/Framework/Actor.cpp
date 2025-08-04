#pragma once
#include "Actor.h"
#include "../Renderer/Model.h"

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
		m_model->Draw(renderer, transform);
	}

	/// <summary>
	/// Returns the effective radius of the actor, based on its model and scale.
	/// </summary>
	/// <returns>The actor's radius as a float. Returns 0 if the model is not set.</returns>
	float Actor::GetRadius()
	{
		return (m_model) ? m_model->GetRadius() * transform.scale * 0.9f : 0;
	}
}
