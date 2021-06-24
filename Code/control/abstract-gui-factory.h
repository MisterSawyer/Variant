#pragma once

#include <memory>

#include "window-interface.h"
#include "button-interface.h"
#include "panel-interface.h"

namespace vrt::gui
{
	class AbstractGUIFactory
	{
	public:
		virtual ~AbstractGUIFactory() = default;

		virtual std::unique_ptr <ButtonInterface> createButton(ButtonBlueprint blueprint, short ID, ControlInterface* parent) const = 0;
		virtual std::unique_ptr <WindowInterface> createWindow(WindowBlueprint blueprint, short ID, ControlInterface * parent) const = 0;
		virtual std::unique_ptr <PanelInterface> createPanel(PanelBlueprint blueprint, short ID, ControlInterface* parent) const = 0;

	};
}