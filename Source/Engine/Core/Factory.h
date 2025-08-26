#pragma once
#include "Framework/Actor.h"
#include "Logger.h"
#include "Singleton.h"
#include "StringHelper.h"
#include <map>
#include <memory>
#include <string>

#define FACTORY_REGISTER(classname) \
class Register##classname           \
{                                   \
public:                             \
    Register##classname()           \
    {                               \
        swaws::Factory::Instance().Register<classname>(#classname); \
    }                               \
};                                  \
Register##classname register_instance;

namespace swaws
{
	class CreatorBase
	{
	public:
		virtual ~CreatorBase() = default;
		virtual std::unique_ptr<Object> Create() = 0;
	};

	template <typename T>
	requires std::derived_from<T, Object>
	class Creator : public CreatorBase
	{
	public:
		std::unique_ptr<Object> Create() override
		{
			return std::make_unique<T>();
		}
	};

	template <typename T>
	requires std::derived_from<T, Object>
	class PrototypeCreator : public CreatorBase
	{
	public:
		PrototypeCreator(std::unique_ptr<T> prototype) :
			prototype{ std::move(prototype) } 
		{ }

		std::unique_ptr<Object> Create() override
		{
			return prototype->Clone();
		}
	private:
		std::unique_ptr<T> prototype;
	};

	class Factory : public Singleton<Factory>
	{
	public:
		template <typename T>
		requires std::derived_from<T, Object>
		void Register(const std::string& name);

		template <typename T>
		requires std::derived_from<T, Object>
		void RegisterPrototype(const std::string& name, std::unique_ptr<T> prototype);

		template <typename T = Object>
		requires std::derived_from<T, Object>
		std::unique_ptr<T> Create(const std::string& name);

		void RemoveAll() { registry.clear(); }
	private:
		std::map<std::string, std::unique_ptr<CreatorBase>> registry;
	};

	/// <summary>
	/// Registers a new type with the factory under the specified name.
	/// </summary>
	/// <typeparam name="T">The type to register. Must be derived from Object.</typeparam>
	/// <param name="name">The name to associate with the type in the factory registry.</param>
	template<typename T>
	requires std::derived_from<T, Object>
	inline void Factory::Register(const std::string& name)
	{
		std::string key = tolower(name);
		registry[key] = std::make_unique<Creator<T>>();
		Logger::Info("Added {} to Registry: ", key);
	}

	/// <summary>
	/// Registers a prototype object in the factory under a specified name.
	/// </summary>
	/// <typeparam name="T">The type of the prototype, which must be derived from Object.</typeparam>
	/// <param name="name">The name to associate with the prototype in the registry.</param>
	/// <param name="prototype">A unique pointer to the prototype object to register.</param>
	template<typename T>
	requires std::derived_from<T, Object>
	inline void Factory::RegisterPrototype(const std::string& name, std::unique_ptr<T> prototype)
	{
		std::string key = tolower(name);
		registry[key] = std::make_unique<PrototypeCreator<T>>(std::move(prototype));
		Logger::Info("Added {} to Registry: ", key);
	}

	/// <summary>
	/// Creates an instance of a registered type derived from Object using its name.
	/// </summary>
	template<typename T>
	requires std::derived_from<T, Object>
	inline std::unique_ptr<T> Factory::Create(const std::string& name)
	{
		std::string key = tolower(name);
		auto it = registry.find(key);
		if (it != registry.end()) {
			std::unique_ptr<Object> base = it->second->Create();
			if (auto* cast = dynamic_cast<T*>(base.get())) {
				base.release(); // transfer ownership
				return std::unique_ptr<T>(cast);
			}
			Logger::Error("Registry contains name: {}, but incorrect type was requested: {}", key, typeid(T).name());
			return {};
		}
		Logger::Error("Registry does not contain name: {}", key);
		return {};
	}

	/// <summary>
	/// Creates a new Actor instance with the specified name and returns a unique pointer to it.
	/// </summary>
	/// <param name="name">The name to assign to the newly created Actor.</param>
	/// <returns>A std::unique_ptr to the newly created Actor.</returns>
	std::unique_ptr<Actor> Instantiate(const std::string& name)
	{
		return Factory::Instance().Create<Actor>(name);
	}

	/// <summary>
	/// Creates and returns a new Actor instance with the specified name, position, rotation, and scale.
	/// </summary>
	/// <param name="name">The name of the Actor to instantiate.</param>
	/// <param name="position">The position of the Actor in 2D space.</param>
	/// <param name="rotation">The rotation of the Actor, in degrees or radians (depending on implementation).</param>
	/// <param name="scale">The scale factor to apply to the Actor.</param>
	/// <returns>A unique pointer to the newly created Actor, or nullptr if creation failed.</returns>
	std::unique_ptr<Actor> Instantiate(const std::string& name, const vec2& position, float rotation, float scale)
	{
		auto actor = Factory::Instance().Create<Actor>(name);
		if (actor) {
			actor->transform = Transform{ position, rotation, scale };
		}
		else Logger::Error("Unable to Instantiate Actor: {}", name);
		return actor;
	}

	/// <summary>
	/// Creates a new Actor instance with the specified name and initializes its transform.
	/// </summary>
	/// <param name="name">The name of the Actor to instantiate.</param>
	/// <param name="transform">The Transform object to assign to the new Actor.</param>
	/// <returns>A unique pointer to the newly created Actor, or nullptr if creation fails.</returns>
	std::unique_ptr<Actor> Instantiate(const std::string& name, Transform& transform)
	{
		auto actor = Factory::Instance().Create<Actor>(name);
		if (actor) {
			actor->transform = transform;
		}
		else Logger::Error("Unable to Instantiate Actor: {}", name);
		return actor;
	}
}