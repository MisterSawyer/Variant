#pragma once

#include "control-win.h"
#include "window-interface.h"

namespace vrt::gui {
	class WindowWin : public ControlWin, public WindowInterface
	{
	public:
		WindowWin(const WindowBlueprint & blueprint, short ID, ControlInterface * parent);
		~WindowWin();

		void show(int cmd_show);

	protected:
		LRESULT __stdcall procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam) override;
	private:
		bool createVariantWindowClass(const WindowBlueprint & blueprint);
		bool createDefaultWindowClass();

	};
}
