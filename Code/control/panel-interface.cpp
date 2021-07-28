#include "panel-interface.h"
#include <iostream>
#include "../log/log.h"
#include <GLM/glm.hpp>

namespace vrt::gui
{
	PanelInterface::PanelInterface(PanelBlueprint blueprint, short ID, ControlInterface* parent)
		: ControlInterface(ID, blueprint, parent)
	{
		LOG_INF("PanelInterface()");
		camera.setViewportSize(getSize());


	}

	render::Camera& PanelInterface::getCamera()
	{
		return camera;
	}

	PanelInterface::~PanelInterface()
	{
		LOG_INF("~PanelInterface()");
	}

	void PanelInterface::update(const std::string& message_from_subject)
	{
		handleEvent(event::Event(event::EventType::Invalidated)); // wysoko poziomowe
		propagateEvent(event::Event(event::EventType::Invalidated)); // nisko poziomowe
	}

	void PanelInterface::setScene(render::Scene* scene_arg)
	{
		scene = scene_arg;
		if (scene != nullptr)
		{
			scene->attach(this);
			handleEvent(event::Event(event::EventType::Invalidated));
			propagateEvent(event::Event(event::EventType::Invalidated)); // nisko poziomowe
		}
		else
		{
			LOG_WAR("Setting empty scene");
		}
	}

	void PanelInterface::render()
	{
		LOG_WAR("Using default empty render method");
	}


	void PanelInterface::handleEvent(const event::Event& event)
	{
		switch (event.type)
		{
		case event::EventType::Invalidated:
		{
			break;
		}
		case event::EventType::Repainted:
		{
			break;
		}
		default:
		{
			break;
		}
		}
	}

}