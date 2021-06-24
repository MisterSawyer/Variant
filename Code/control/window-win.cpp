#include "window-win.h"
#include "../log/log.h"

namespace vrt::gui
{
	/*
	* 
	*/
	WindowWin::WindowWin(const WindowBlueprint & blueprint, short ID, ControlInterface * parent)
		: WindowInterface(blueprint, ID, parent), ControlWin(blueprint, ID)
	{
		bool success = true;

		LOG_INF("Creating new class " + getFullClassName() + " of type " + getClassType());
			
		WNDCLASS win_class;
		if (!GetClassInfo(reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)), getFullClassName().c_str(), &win_class))
		{
			/*
			* if this type does not exists then create it
			*/
			if (!createDefaultWindowClass())success = false;

			/*
			* First we save default_procedure for this type of classes
			*/		
			if(!createVariantWindowClass(blueprint)) success = false;
		}
		
		setStyle(WS_OVERLAPPEDWINDOW);


		if (parent != nullptr)
		{
			ControlWin* parent_win_control = dynamic_cast<ControlWin*>(parent);
			if (parent_win_control == nullptr)
			{
				LOG_ERR("Parent is not windows control");
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

		if(success)setAsInitialized();

		LOG_ASSERT_MSG(success, getFullClassName() + " not initialized");
	}

	bool WindowWin::createDefaultWindowClass()
	{
		WNDCLASSEX win_class;
		if (!GetClassInfoExA(reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)), getClassType().c_str(), &win_class))
		{
			LOG_INF("Class type " + getClassType() + " does not exist, creating new one.");
			WNDCLASSEX class_type = { 0 };
			class_type.cbSize = sizeof(WNDCLASSEX);
			class_type.cbClsExtra = 0;
			class_type.cbWndExtra = 0;
			class_type.hInstance = reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr));
			class_type.hCursor = LoadCursor(0, IDC_ARROW);
			class_type.hIconSm = 0;
			class_type.hIcon = 0;
			class_type.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
			class_type.lpfnWndProc = linkProcedure;
			class_type.lpszClassName = getClassType().c_str();
			class_type.lpszMenuName = nullptr;
			class_type.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

			return registerClass(class_type);
		}

		return true;
	}

	bool WindowWin::createVariantWindowClass(const WindowBlueprint& blueprint)
	{
		/*
		* If this class does not yet exists then create new one:
		*/
		WNDCLASSEX class_type;
		class_type.cbSize = sizeof(WNDCLASSEX);

		if (!GetClassInfoExA(reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)), getFullClassName().c_str(), &class_type))
		{
			if (!GetClassInfoExA(reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)), getClassType().c_str(), &class_type))
			{
				LOG_ERR("Cannot create Variant class because base type" + getClassType() + "does not exist. " + log::GetLastErrorAsString());
				return false;
			}

			class_type.lpfnWndProc = linkProcedure; // this will link procedure at WM_CREATE 
			class_type.lpszClassName = getFullClassName().c_str();
			class_type.style = 0; // CS_HREDRAW | CS_VREDRAW;

			return registerClass(class_type);
		}
		return true;
	}

	LRESULT __stdcall WindowWin::procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
	{
		event::Event new_event;

		switch (message)
		{
		case WM_COMMAND:
		{
			switch (HIWORD(wparam))
			{
			case BN_CLICKED:
			{
				new_event.type = event::EventType::LClick;
				new_event.params.push_back(LOWORD(wparam));
				break;
			}
			}
			break;
		}

		case WM_DESTROY:
		{
			new_event.type = event::EventType::Destroy;
			PostQuitMessage(0);
			break;
		}

		case WM_CLOSE:
		{
			new_event.type = event::EventType::Close;
			DestroyWindow(window);
			break;
		}

		case WM_PAINT:
		{
			new_event.type = event::EventType::Repaint;
			break;
		}
		case WM_SIZE:
		{
			new_event.type = event::EventType::Resize;
			setSize(static_cast<LONG>(LOWORD(lparam)), static_cast<LONG>(HIWORD(lparam)));
			break;
		}
		}

		if(new_event.type != event::EventType::None)handleEvent(new_event);

		return DefWindowProcA(window, message, wparam, lparam);
	}

	void WindowWin::show(int cmd_show)
	{
		ShowWindow(getHandle(), cmd_show);
		UpdateWindow(getHandle());
	}

	WindowWin::~WindowWin()
	{
		
		LOG_INF("~WindowWin()");
	}
}