#pragma once

#include "Scene.h"
#include "Actor.h"
#include "Engine.h"
#include "Renderer/Renderer.h"

namespace swaws
{
	static bool LineCircleCollision(const swaws::vec2& lineStart, const swaws::vec2& lineEnd, const swaws::vec2& circleCenter, float circleRadius) {
		swaws::vec2 lineVec = lineEnd - lineStart;
		swaws::vec2 toCircle = circleCenter - lineStart;
		float t = swaws::vec2::Dot(toCircle, lineVec) / swaws::vec2::Dot(lineVec, lineVec);
		t = std::clamp(t, 0.0f, 1.0f);
		swaws::vec2 closest = lineStart + lineVec * t;
		return (circleCenter - closest).Length() < circleRadius;
	}

	/// <summary>
	/// Updates all actors in the scene by advancing their state based on the elapsed time.
	/// </summary>
	/// <param name="dt">The time elapsed since the last update, in seconds.</param>
	void Scene::Update(float dt)
	{
		// Update All Actors
		for (auto& act : m_actors)
		{
			act->Update(dt);
		}

		// Remove Destroyed Actors
		for (auto iter = m_actors.begin(); iter != m_actors.end();)
		{
			if ((*iter)->destroyed) iter = m_actors.erase(iter);
			else iter++;
		}

		// Check for collisions
		for (auto& actorA : m_actors)
		{
			for (auto& actorB : m_actors)
			{
				if (actorA == actorB || (actorA->destroyed || actorB->destroyed)) continue;
				
				float distance = (actorA->transform.position - actorB->transform.position).Length();
				if (distance <= (actorA->GetRadius() + actorB->GetRadius()))
				{
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}

				// Straight-Line Collision Checks (Sight Checks?)
				if (actorA->name == "laser") {
					vec2 laserStart = actorA->transform.position;
					vec2 laserDir = vec2{ 1, 0 }.Rotate(math::DegToRad(actorA->transform.rotation));
					vec2 laserEnd = laserStart + laserDir * actorA->length;

					vec2 circleCenter = actorB->transform.position;
					float circleRadius = actorB->GetRadius();

					if (LineCircleCollision(laserStart, laserEnd, circleCenter, circleRadius)) {
						actorA->OnCollision(actorB.get());
						actorB->OnCollision(actorA.get());
					}
				}
			}
		}
	}

	/// <summary>
	/// Draws all actors in the scene using the specified renderer.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the actors.</param>
	void Scene::Draw(Renderer& renderer)
	{
		for (auto& act : m_actors)
		{
			act->Draw(renderer);
		}
	}

	/// <summary>
	/// Adds an actor to the scene.
	/// </summary>
	/// <param name="act">A unique pointer to the actor to be added.</param>
	void Scene::AddActor(std::unique_ptr<Actor> act)
	{
		act->scene = this;
		m_actors.push_back(std::move(act));
	}

	void Scene::RemoveAllActors()
	{
		m_actors.clear();
	}

}