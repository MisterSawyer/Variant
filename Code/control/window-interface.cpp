#include "window-interface.h"
#include <iostream>
#include "../log/log.h"

namespace vrt::gui
{
	WindowInterface::WindowInterface(WindowBlueprint blueprint, short ID, ControlInterface* parent)
		: ControlInterface(ID, blueprint, parent) 
	{
		LOG_INF("WindowInterface()");
	}

	WindowInterface::~WindowInterface()
	{
		LOG_INF("~WindowInterface()");
	}

	void WindowInterface::handleEvent(const event::Event& event)
	{
		//TODO
	}
}