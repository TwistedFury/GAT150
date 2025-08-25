#include "EnginePCH.h"


namespace swaws
{
	void EventManager::AddObserver(const Event::id_t& id, IObserver& observer)
	{
		observers[id].push_back(&observer);
	}

	void EventManager::RemoveObserver(IObserver& observer)
	{
		IObserver* observerPtr = &observer;

		for (auto& eventType : observers)
		{
			// Get list of observers for event type
			auto observers = eventType.second;

			// Remove matching observers from event type
			std::erase_if(observers, [observerPtr](auto observer)
			{
				return (observer == observerPtr);
			});
		}
	}

	void EventManager::Notify(const Event& event)
	{

	}
}
