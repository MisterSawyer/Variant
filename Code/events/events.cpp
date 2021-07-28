#include "events.h"

namespace vrt::gui::event
{
	Event::Event()
	: type(EventType::None)
	{
	}

	Event::Event(const EventType& type_arg)
		:type(type_arg)
	{
	}
}