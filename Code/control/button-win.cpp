#include "button-win.h"
#include "../log/log.h"


namespace vrt::gui
{
	ButtonWin::ButtonWin(ButtonBlueprint blueprint, short ID, ControlInterface* parent)
		: ButtonInterface(blueprint, ID, parent), ControlWin(blueprint, ID)
	{
		bool success = true;

		LOG_INF("Creating new class " + getFullClassName() + " of type " + getClassType());

		WNDCLASS win_class;
		if (!GetClassInfo(reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)), getFullClassName().c_str(), &win_class))
		{
			/*
			* First we save default_procedure for this type of classes
			*/
			if (!createVariantButtonClass(blueprint)) success = false;
		}

		setStyle(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON);

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


	bool ButtonWin::createVariantButtonClass(const ButtonBlueprint& blueprint)
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

			return registerClass(class_type);
		}
		return true;
	}

	ButtonWin::~ButtonWin()
	{
		LOG_INF("~ButtonWin()");
	}
}