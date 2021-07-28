#pragma once
#include <vector>
#include <iostream>

namespace vrt::gui::event
{
	enum class EventType
	{
		None, Close, Repainted, Invalidated, Resize, Create, Destroy, LClick, RClick, DoubleClick, GainFocus, KillFocus, TextEntered
	};

	struct Event
	{
		Event();
		explicit Event(const EventType & type);

		EventType type;
		std::vector<int> params;
		std::string additional_parameters;
	};
}