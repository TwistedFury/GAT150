#pragma once

namespace swaws
{
	class IObserver
	{
	public:
		~IObserver() = default;

		virtual void OnNotify(const Event& event) = 0;
	};
}