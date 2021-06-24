#pragma once

#include "control-win.h"
#include "panel-interface.h"


namespace vrt::gui {
	class PanelWin : public ControlWin, public PanelInterface
	{
	public:
		PanelWin(const PanelBlueprint& blueprint, short ID, ControlInterface* parent);
		~PanelWin();

		void show(int cmd_show);

	protected:
		LRESULT __stdcall procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam) override;
	private:
		bool createVariantPanelClass(const PanelBlueprint & blueprint);

		
		HGLRC render_context_handle;
	};
}
