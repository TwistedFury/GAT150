#include "Observer.h"

namespace swaws
{
	IObserver::~IObserver()
	{
		OBSERVER_REMOVE_SELF;
	}
}