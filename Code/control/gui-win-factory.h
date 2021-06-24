#pragma once
#include "abstract-gui-factory.h"

#include <Windows.h>
#include <memory>
#include <gdiplus.h>


namespace vrt::gui
{
	class GUIWinFactory : public AbstractGUIFactory
	{
	public:
		GUIWinFactory();
		~GUIWinFactory();

		std::unique_ptr <ButtonInterface> createButton(ButtonBlueprint blueprint, short ID, ControlInterface* parent) const override;
		std::unique_ptr <WindowInterface> createWindow(WindowBlueprint blueprint, short ID, ControlInterface * parent) const override;
		std::unique_ptr <PanelInterface> createPanel(PanelBlueprint blueprint, short ID, ControlInterface* parent)const override;

	private:
		HINSTANCE instance;
		Gdiplus::GdiplusStartupInput	gdi_startupinput;
		ULONG_PTR						gdi_token;
	};
}