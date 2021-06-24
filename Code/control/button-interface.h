#pragma once

#include "control-interface.h"
#include "button-blueprint.h"


namespace vrt::gui
{
	class ButtonInterface : public ControlInterface
	{
	public:
		ButtonInterface(ButtonBlueprint blueprint, short ID, ControlInterface* parent);
		virtual ~ButtonInterface();
	protected:
		//void handleEvent(const event::Event& event) final;
	private:

	};
}