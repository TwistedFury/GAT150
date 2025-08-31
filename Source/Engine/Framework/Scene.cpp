#pragma once

#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Components/ColliderComponent.h"
#include "Scene.h"

namespace swaws
{
	void Scene::Read(const json::value_t& value)
	{
		// Read Prototypes
		if (JSON_HAS(value, prototypes))
		{
			for (auto& actorVal : JSON_GET(value, prototypes).GetArray())
			{
				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(actorVal);

				std::string name = actor->name;
				Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
			}
		}

		if (JSON_HAS(value, actors))
		{
			for (auto& actorVal : JSON_GET(value, actors).GetArray())
			{
				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(actorVal);

				AddActor(std::move(actor), false);
			}
		}
		else Logger::Error("Document does not contain \"actors\"");
	}

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
		// Update All Actors (only those active and not pending removal)
		for (auto& act : m_actors)
		{
			if (act && act->isActive && !act->destroyed) act->Update(dt);
		}

		std::erase_if(m_actors, [](auto& actor)
		{
			return actor->destroyed;
		});

		// Check for collisions
		for (auto& actorA : m_actors)
		{
			if (!actorA->isActive || actorA->destroyed) continue;

			for (auto& actorB : m_actors)
			{
				if (actorA == actorB) continue;
				if (!actorB->isActive || actorB->destroyed) continue;

				auto colliderA = actorA->GetComponent<ColliderComponent>();
				auto colliderB = actorB->GetComponent<ColliderComponent>();
				if (!colliderA || !colliderB) continue;

				if (colliderA->CheckCollision(*colliderB))
				{
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
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
			if (act && act->GetObjectIsActive()) act->Draw(renderer);
		}
	}

	bool Scene::Load(const std::string& sceneName)
	{
		swaws::json::document_t document;
		if (swaws::json::Load(sceneName, document)) Read(document);
		else {
			Logger::Error("Scene {} not loaded properly", sceneName);
			return false;
		}

		// Start Actors
		for (auto& actor : m_actors) actor->Start();

		return true;
	}

	/// <summary>
	/// Adds an actor to the scene.
	/// </summary>
	/// <param name="act">A unique pointer to the actor to be added.</param>
	void Scene::AddActor(std::unique_ptr<Actor> act, bool start)
	{
		if (act)
		{
			act->scene = this;
			if (start) act->Start();
			m_actors.push_back(std::move(act));
		}
	}

	void Scene::RemoveAllActors(bool force)
	{
		if (!force)
		{
			// Check Persistence
			for (auto iter = m_actors.begin(); iter != m_actors.end();)
			{
				if (!(*iter)->persistent) iter = m_actors.erase(iter);
				else iter++;
			}
		}
		else m_actors.clear();
	}
}