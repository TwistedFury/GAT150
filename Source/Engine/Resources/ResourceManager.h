#pragma once

#include "Core/StringHelper.h"
#include "Resource.h"
#include <map>
#include <memory>
#include <iostream>
#include <utility>

namespace swaws
{
	class ResourceManager : public Singleton<ResourceManager>
	{
	public:
		void RemoveAll() { m_resources.clear(); }

		template <typename T, typename ... Args>
		requires std::derived_from<T, Resource>
		res_t<T> Get(const std::string& name, Args&& ... args);

		template <typename T, typename ... Args>
		requires std::derived_from<T, Resource>
		res_t<T> GetWithID(const std::string& id, const std::string& name, Args&& ... args);

	private:
		std::map<std::string, res_t<Resource>> m_resources;

		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
	};

	template<typename T, typename ... Args>
	requires std::derived_from<T, Resource>
	inline res_t<T> ResourceManager::Get(const std::string& name, Args&& ... args)
	{
		return GetWithID<T>(name, name, std::forward<Args>(args)...);
	}

	template<typename T, typename ... Args>
	requires std::derived_from<T, Resource>
	inline res_t<T> ResourceManager::GetWithID(const std::string& id, const std::string& name, Args&& ...args)
	{
		std::string key = tolower(id);
		auto iter = m_resources.find(key);
		if (iter != m_resources.end())
		{
			auto& base = iter->second;
			auto derived = std::dynamic_pointer_cast<T>(base);
			if (derived == nullptr) {
				Logger::Warning("Resource Type Mismatch: {}", key);
			}

			return derived;
		}
		// Doesn't Exist
		res_t<T> resource = std::make_shared<T>();
		if (!resource->Load(name, std::forward<Args>(args)...))
		{
			Logger::Error("Could not load resource: {}", name);
			return res_t<T>();
		}
		m_resources[key] = resource;

		return resource;
	}

	inline ResourceManager& Resources() { return ResourceManager::Instance(); }

}