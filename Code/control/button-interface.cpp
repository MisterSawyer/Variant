#include "button-interface.h"
#include "../log/log.h"

namespace vrt::gui
{
	ButtonInterface::ButtonInterface(ButtonBlueprint blueprint, short ID, ControlInterface* parent)
	:	ControlInterface(ID, blueprint, parent) 
	{
		LOG_INF("ButtonInterface()");
	}

	ButtonInterface::~ButtonInterface()
	{
		LOG_INF("~ButtonInterface()");
	}
}