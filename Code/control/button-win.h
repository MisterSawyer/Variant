#pragma once

#include "control-win.h"
#include "button-interface.h"

namespace vrt::gui {
	class ButtonWin : public ControlWin, public ButtonInterface
	{
	public:
		ButtonWin(ButtonBlueprint blueprint, short ID, ControlInterface* parent);
		~ButtonWin();
	protected:

	private:
		bool createVariantButtonClass(const ButtonBlueprint& blueprint);
	};
}
