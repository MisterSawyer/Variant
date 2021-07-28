#include "panel-win.h"
#include "../log/log.h"
#include <GL/glew.h>
#include <GL/wglew.h>


namespace vrt::gui
{
	/*
	*
	*/
	PanelWin::PanelWin(const PanelBlueprint& blueprint, short ID, ControlInterface* parent)
		: PanelInterface(blueprint, ID, parent), ControlWin(blueprint, ID)
	{
		bool success = true;

		LOG_INF("Creating new class " + getFullClassName() + " of type " + getClassType());

		WNDCLASS win_class;
		if (!GetClassInfo(reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)), getFullClassName().c_str(), &win_class))
		{
			if (!createVariantPanelClass(blueprint)) success = false;
		}

		setStyle(WS_CHILD | WS_BORDER);


		if (parent != nullptr)
		{
			ControlWin* parent_win_control = dynamic_cast<ControlWin*>(parent);
			if (parent_win_control == nullptr)
			{
				LOG_ERR("Parent is not windows controll");
				success = false;
			}
			else
			{
				if (!ControlWin::create(blueprint, parent_win_control->getHandle()))success = false;
			}
		}
		else
		{
			if (!ControlWin::create(blueprint, nullptr))success = false;
		}

		if (success)setAsInitialized();

		LOG_ASSERT_MSG(success, getFullClassName() + " not initialized");
	}

	bool PanelWin::createVariantPanelClass(const PanelBlueprint& blueprint)
	{
		/*
		* If this class does not yet exists then create new one:
		*/
		WNDCLASS class_type;

		if (!GetClassInfo(reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)), getFullClassName().c_str(), &class_type))
		{
			if (!GetClassInfo(reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)), getClassType().c_str(), &class_type))
			{
				LOG_ERR("Cannot create Variant class because base type" + getClassType() + "does not exist. " + log::GetLastErrorAsString());
				return false;
			}

			class_type.lpfnWndProc = linkProcedure; // this will link procedure at WM_CREATE 
			class_type.lpszClassName = getFullClassName().c_str();

			/*
			* Register new class
			*/

			if (!RegisterClass(&class_type))
			{
				LOG_ERR("Registering class " + getFullClassName() + " failed. " + log::GetLastErrorAsString());
				return false;
			}
			else
			{
				LOG_INF("Class " + getFullClassName() + " created.");
			}
		}
		return true;
	}

	void PanelWin::propagateEvent(const event::Event& event)
	{
		switch (event.type)
		{
			case event::EventType::Invalidated: RedrawWindow(getHandle(), nullptr, nullptr, RDW_INTERNALPAINT); return;
		}
	}

	void PanelWin::render()
	{

		PAINTSTRUCT ps;
		HDC dc = BeginPaint(getHandle(), &ps);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (scene != nullptr)scene->display(camera.getMatrix());
		else LOG_WAR("Empty scene to draw");

		SwapBuffers(dc);
		EndPaint(getHandle(), &ps);
	}


	void PanelWin::show(int cmd_show)
	{
		ShowWindow(getHandle(), cmd_show);
		UpdateWindow(getHandle());
	}

	PanelWin::~PanelWin()
	{

		LOG_INF("~PanelWin()");
	}
}