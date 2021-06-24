#pragma once
#include "control-interface.h"

#include <Windows.h>
#include <gdiplus.h>


namespace vrt::gui
{
	class ControlWin
	{
	public:
		ControlWin(const ControlBlueprint& blueprint, short ID);
		virtual ~ControlWin();

		HWND getHandle() const;
		static void setInstance(HINSTANCE instance);

	protected:
		bool create(const ControlBlueprint & blueprint, HWND parent_handle);

		/*
		* Called when event obtained
		*/
		virtual LRESULT __stdcall procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

		/*
		* Called when created - used to link procedure to object 
		*/
		static LRESULT __stdcall linkProcedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
		
		void setHandle(HWND handle);
		void setHMenu(HMENU hmenu);

		HMENU getHMenu() const;

		void setStyle(DWORD style);
		DWORD getStyle();

		WNDPROC default_procedure;

		const std::string& getClassType();
		const std::string& getFullClassName();

		static bool registerClass(WNDCLASSEX new_class);
		static bool registerClass(WNDCLASS new_class);
		static HINSTANCE getInstance();
		static bool unregisterClass(LPCSTR class_);

	private:
		void setClassType(const std::string& type);
		void setFullClassName(const std::string& full_name);

		std::string class_type;
		std::string full_class_name;

		static HINSTANCE instance;

		DWORD style;
		HWND handle;
		HMENU hmenu;
	};
}
