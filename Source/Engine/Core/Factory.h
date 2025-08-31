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
		constexpr bool isActor = std::is_base_of_v<Actor, T>;
		if (isActor) registry[key] = std::make_unique<Creator<Actor>>();
		else registry[key] = std::make_unique<Creator<T>>();
		Logger::Info("Added {} to Registry", key);
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
	/// <typeparam name="T">The type to instantiate. Must be derived from Object.</typeparam>
	/// <param name="name">The name of the type to create an instance of.</param>
	/// <returns>A unique pointer to the newly created instance of type T, or nullptr if the name is not found in the registry.</returns>
	template<typename T>
	requires std::derived_from<T, Object>
	inline std::unique_ptr<T> Factory::Create(const std::string& name)
	{
		std::string key = tolower(name);
		auto it = registry.find(key);
		if (it != registry.end()) {
			auto object = it->second->Create();
			constexpr bool isActor = std::is_base_of_v<Actor, T>;
			if (isActor) return std::unique_ptr<T>(static_cast<T*>(object.release()));
			else {
				auto derived = dynamic_cast<T*>(object.get());
				if (derived) return std::unique_ptr<T>(static_cast<T*>(object.release()));
				else Logger::Error("Registry contains name: {}, but incorrect type was provided: {}", key, typeid(T).name());
				return nullptr;
			}
		}
		Logger::Error("Registry does not contain name: {}", key);
		return nullptr;
	}

	inline std::unique_ptr<Actor> Instantiate(const std::string& name)
	{
		return Factory::Instance().Create<Actor>(name);
	}

	inline std::unique_ptr<Actor> Instantiate(const std::string& name, const vec2& position, float rotation, float scale)
	{
		auto actor = Factory::Instance().Create<Actor>(name);
		if (actor) actor->transform = Transform{ position, rotation, scale };
		else Logger::Error("Unable to Instantiate Actor: {}", name);
		return actor;
	}

	inline std::unique_ptr<Actor> Instantiate(const std::string& name, Transform& transform)
	{
		auto actor = Factory::Instance().Create<Actor>(name);
		if (actor) actor->transform = transform;
		else Logger::Error("Unable to Instantiate Actor: {}", name);
		return actor;
	}
}