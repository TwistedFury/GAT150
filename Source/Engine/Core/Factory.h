#pragma once
#include "Framework/Object.h"
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

	class Factory : public Singleton<Factory>
	{
	public:
		template <typename T>
		requires std::derived_from<T, Object>
		void Register(const std::string& name);

		template <typename T = Object>
		requires std::derived_from<T, Object>
		std::unique_ptr<T> Create(const std::string& name);
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
		Logger::Info("Added {} to Registry", key);
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
			auto object =  it->second->Create();
			T* derived = dynamic_cast<T*>(object.get());
			if (derived) return std::unique_ptr<T>(derived);
			else Logger::Error("Registry contains name: {}, but incorrect type was provided: {}", key, typeid(T).name());
		}
		Logger::Error("Registry does not contain name: {}", key);
		return nullptr;
	}
}