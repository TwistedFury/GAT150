#pragma once

namespace swaws
{
	class IObserver
	{
	public:
		~IObserver();

		virtual void OnNotify(const Event& event) = 0;
	};
}