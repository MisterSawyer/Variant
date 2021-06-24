#include "panel-interface.h"
#include <iostream>
#include "../log/log.h"

namespace vrt::gui
{
	PanelInterface::PanelInterface(PanelBlueprint blueprint, short ID, ControlInterface* parent)
		: ControlInterface(ID, blueprint, parent)
	{
		LOG_INF("PanelInterface()");
	}

	PanelInterface::~PanelInterface()
	{
		LOG_INF("~PanelInterface()");
	}

	void PanelInterface::update(const std::string& message_from_subject)
	{
		 //TODO event paint
	}

	void PanelInterface::setScene(render::Scene* scene_arg)
	{
		scene = scene_arg;
	}

	/*
	void PanelInterface::handleEvent(const event::Event& event)
	{
		std::cout << (int)event.type << std::endl;
		//TODO
	}
	*/
}