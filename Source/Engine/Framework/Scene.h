#pragma once

#include <vector>
#include <string>
#include <list>
#include <memory>
#include "Core/StringHelper.h"

namespace swaws
{
	class Game;
	class Scene
	{
	public:
		Scene(Game* game) : m_game{ game } {}

		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddActor(std::unique_ptr<class Actor> act);
		void RemoveAllActors();

		std::list<std::unique_ptr<class Actor>>& GetActors() { return m_actors; }

		template <typename T = Actor>
		T* GetActorByName(const std::string& name);

		template <typename T = Actor>
		std::vector<T*> GetActorsByTag(const std::string& tag);

		Game* GetGame() { return m_game; }

	private:
		Game* m_game{ nullptr };
		std::list<std::unique_ptr<class Actor>> m_actors;
	};

	using swaws::tolower;

	/// <summary>
	/// Retrieves all actors in the scene with a matching tag and casts them to the specified type.
	/// </summary>
	/// <typeparam name="T">The type to which matching actors will be cast.</typeparam>
	/// <param name="tag">The tag to match against each actor's tag.</param>
	/// <returns>A vector of pointers to actors of type T whose tag matches the specified tag.</returns>
	template<typename T>
	inline std::vector<T*> Scene::GetActorsByTag(const std::string& tag)
	{
		std::vector<T*> results;
		for (auto& actor : m_actors)
		{
			if (tolower(actor->tag) == tolower(tag))
			{
				T* object = dynamic_cast<T*>(actor.get());
				if (object) results.push_back(object);
			}
		}

		return results;
	}

	/// <summary>
	/// Retrieves an actor from the scene by name and casts it to the specified type.
	/// </summary>
	/// <typeparam name="T">The type to cast the found actor to.</typeparam>
	/// <param name="name">The name of the actor to search for (case-insensitive).</param>
	/// <returns>A pointer to the actor of type T if found; otherwise, nullptr.</returns>
	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto& actor : m_actors)
		{
			if (tolower(actor->name) == tolower(name))
			{
				T* object = dynamic_cast<T*>(actor.get());
				if (object) return object;
			}
		}
		return nullptr;
	}
}