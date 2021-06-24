#pragma once
#include <vector>
#include <iostream>

namespace vrt::gui::event
{
	enum class EventType
	{
		None, Close, Repaint, Resize, Create, Destroy, LClick, RClick, DoubleClick, GainFocus, KillFocus, TextEntered
	};

	struct Event
	{
		Event();

		EventType type;
		std::vector<int> params;
		std::string additional_parameters;
	};
}