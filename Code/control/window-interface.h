#pragma once

#include "control-interface.h"
#include "window-blueprint.h"

namespace vrt::gui
{
	class WindowInterface : public ControlInterface
	{
	public:
		WindowInterface(WindowBlueprint blueprint, short ID, ControlInterface* parent);
		virtual ~WindowInterface();

		virtual void show(int cmd_show) = 0;
	protected:
		void handleEvent(const event::Event& event) final;

	private:

	};
}