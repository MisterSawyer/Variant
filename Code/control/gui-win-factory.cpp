#include "gui-win-factory.h"

#include "button-win.h"
#include "window-win.h"
#include "panel-win.h"

#include "../log/log.h"

namespace vrt::gui
{

	GUIWinFactory::GUIWinFactory() 
	{
		Gdiplus::GdiplusStartup(&gdi_token, &gdi_startupinput, nullptr);

		instance = (HINSTANCE)GetModuleHandle(nullptr);
		LOG_INF("GUIWinFactory created " << instance);
		ControlWin::setInstance(instance);
	}

	GUIWinFactory::~GUIWinFactory()
	{
		LOG_INF("GUIWinFactory destroyed " << instance);
		Gdiplus::GdiplusShutdown(gdi_token);
	}

	std::unique_ptr<ButtonInterface>GUIWinFactory::createButton(ButtonBlueprint blueprint, short ID, ControlInterface* parent) const
	{
		return std::make_unique<ButtonWin>(std::move(blueprint), ID, parent);
	}

	std::unique_ptr<WindowInterface> GUIWinFactory::createWindow(WindowBlueprint blueprint, short ID, ControlInterface* parent) const
	{
		return std::make_unique<WindowWin>(std::move(blueprint), ID, parent);
	}

	std::unique_ptr <PanelInterface> GUIWinFactory::createPanel(PanelBlueprint blueprint, short ID, ControlInterface* parent)const
	{
		return std::make_unique<PanelWin>(std::move(blueprint), ID, parent);
	}

}