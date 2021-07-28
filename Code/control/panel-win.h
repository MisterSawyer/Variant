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
		void render() override;
	protected:
		void propagateEvent(const event::Event& event) final;
		LRESULT __stdcall procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam) override;
	private:
		bool createVariantPanelClass(const PanelBlueprint & blueprint);
		glm::vec2 mouse_position;
		HDC device_context_handle;
		HGLRC render_context_handle;
	};
}
