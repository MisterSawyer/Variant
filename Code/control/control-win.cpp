#include "control-win.h"
#include "../log/log.h"



namespace vrt::gui
{

	HINSTANCE ControlWin::instance = 0;

	ControlWin::ControlWin(const ControlBlueprint& blueprint, short ID)
	{
		LOG_INF("ControlWin() "<< ID);
		/*
		* Set variables for this particular control
		*/

		setHMenu(reinterpret_cast<HMENU>(ID));
		setClassType(blueprint.getControlClassName());
		setFullClassName("Variant_" + blueprint.getControlClassName());
	}

	ControlWin::~ControlWin()
	{
		//TODO mozliwe Destroy Window
		LOG_INF("~ControlWin()");
	}

	bool ControlWin::unregisterClass(LPCSTR class_)
	{
		/*
		if (!UnregisterClass(class_, instance))
		{
			LOG_ERR("Unregistering class " + std::string(class_) + " failed. " + log::GetLastErrorAsString());
			return false;
		}
		else
		{
			LOG_INF("Class " + std::string(class_) + " destroyed.");
		}
		*/
		return true;
	}

	bool ControlWin::registerClass(WNDCLASSEX new_class)
	{
		if (!RegisterClassExA(&new_class))
		{
			LOG_ERR("Registering class " + std::string(new_class.lpszClassName) + " failed. " + log::GetLastErrorAsString());
			return false;
		}
		else
		{
			LOG_INF("Class " + std::string(new_class.lpszClassName) + " created.");
		}
		return true;
	}

	bool ControlWin::registerClass(WNDCLASS new_class)
	{
		if (!RegisterClass(&new_class))
		{
			LOG_ERR("Registering class [EX] " + std::string(new_class.lpszClassName) + " failed. " + log::GetLastErrorAsString());
			return false;
		}
		else
		{
			LOG_INF("Class " + std::string(new_class.lpszClassName) + " created.");
		}
		return true;
	}

	void ControlWin::setInstance(HINSTANCE instance_arg)
	{
		instance = instance_arg;
	}

	HINSTANCE ControlWin::getInstance()
	{
		return instance;
	}

	LRESULT __stdcall ControlWin::linkProcedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
	{ 
		ControlWin * control = nullptr;
		if (message == WM_CREATE)
		{
			CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lparam);
			control = reinterpret_cast<ControlWin*>(cs->lpCreateParams);

			SetLastError(0);
			bool success = SetWindowLongPtrA(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(control)) != 0;
			if (!success && GetLastError() != 0)
			{
				LOG_ERR("Procedure matching failed.");
				DestroyWindow(window);
				return -1;
			}
		}
		else
		{
			control = reinterpret_cast<ControlWin*>(GetWindowLongPtr(window, GWLP_USERDATA));
		}

		return control != nullptr ? control->procedure(window, message, wparam, lparam) : DefWindowProc(window, message, wparam, lparam);
	}

	bool ControlWin::create(const ControlBlueprint& blueprint, HWND parent_handle)
	{
		/*
		* Tutaj w³aœciwie mozna od razu ³apaæ default_procedure
		*/
		WNDCLASS control_class_type_default;
		if (!GetClassInfo(reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)), getClassType().c_str(), &control_class_type_default))
		{
			LOG_ERR("Preparing window class tye" + getClassType() + " failed.");
			return false;
		}

		/*
		* Save default procedure
		*/
		default_procedure = control_class_type_default.lpfnWndProc;


		HWND handle = CreateWindowEx(0, getFullClassName().c_str(), getClassType().c_str(), getStyle(), 
			blueprint.position.x, blueprint.position.y, blueprint.size.x, blueprint.size.y,
			parent_handle,
			getHMenu(), reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)), this); // getStyle = WS_CHILD | WS_BORDER

		setHandle(handle);

		if (handle == 0)
		{
			LOG_ERR("Creating object of class " + getFullClassName() + " failed.");
			return false;
		}
		return true;
	}

	LRESULT __stdcall ControlWin::procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
	{
		return CallWindowProcA(default_procedure, window, message, wparam, lparam);
	}

	void ControlWin::setHandle(HWND handle_arg)
	{
		handle = handle_arg;
	}

	void ControlWin::setHMenu(HMENU hmenu_arg)
	{
		hmenu = hmenu_arg;
	}

	HWND ControlWin::getHandle() const
	{
		return handle;
	}

	HMENU ControlWin::getHMenu() const
	{
		return hmenu;
	}

	const std::string& ControlWin::getClassType()
	{
		return class_type;
	}

	const std::string& ControlWin::getFullClassName()
	{
		return full_class_name;
	}

	void ControlWin::setClassType(const std::string& type_arg)
	{
		class_type = type_arg;
	}

	void ControlWin::setFullClassName(const std::string& full_name_arg)
	{
		full_class_name = full_name_arg;
	}

	void ControlWin::setStyle(DWORD style_arg)
	{
		style = style_arg;
	}
	
	DWORD ControlWin::getStyle()
	{
		return style;
	}
}