#include "panel-win.h"
#include "../log/log.h"
#include <GL/glew.h>
#include <GL/wglew.h>

#include "window-win.h"

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

	LRESULT __stdcall PanelWin::procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
	{
		event::Event new_event;

		switch (message)
		{
		case WM_CREATE:
		{
			
			WNDCLASSEX class_type = { 0 };
			class_type.cbSize = sizeof(WNDCLASSEX);
			class_type.cbClsExtra = 0;
			class_type.cbWndExtra = 0;
			class_type.hInstance = reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr));
			class_type.hCursor = LoadCursor(0, IDC_ARROW);
			class_type.hIconSm = 0;
			class_type.hIcon = 0;
			class_type.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
			class_type.lpfnWndProc = DefWindowProc;
			class_type.lpszClassName = "OPENGL21TEMP";
			class_type.lpszMenuName = nullptr;
			class_type.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
			
			ControlWin::registerClass(class_type);
			
			HWND tmp_window = CreateWindowEx(0, "OPENGL21TEMP", "OPENGL21TEMP", WS_POPUP | WS_BORDER,
				0, 0, 300, 300,
				nullptr,
				0,
				reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)), this);

			if (tmp_window == 0)
			{
				LOG_ERR(log::GetLastErrorAsString());
				ControlWin::unregisterClass("OPENGL21TEMP");
				return -1;
			}
			

			PIXELFORMATDESCRIPTOR pfd = { 0 };
			pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
			pfd.cColorBits = 24;
			pfd.cAlphaBits = 8;
			pfd.cDepthBits = 24;
			pfd.cStencilBits = 8;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.iLayerType = PFD_MAIN_PLANE;
			HDC dc = GetDC(tmp_window);

			int pf = ChoosePixelFormat(dc, &pfd);
			if (!SetPixelFormat(dc, pf, &pfd))
			{
				LOG_ERR(log::GetLastErrorAsString());
				ReleaseDC(tmp_window, dc);
				DestroyWindow(tmp_window);
				ControlWin::unregisterClass("OPENGL21TEMP");
				return -1;
			}

			HGLRC rc = wglCreateContext(dc);
			
			if (rc == 0)
			{
				LOG_ERR(log::GetLastErrorAsString());
				ReleaseDC(tmp_window, dc);
				DestroyWindow(tmp_window);
				ControlWin::unregisterClass("OPENGL21TEMP");
				return -1;
			}

			if (!wglMakeCurrent(dc, rc))
			{
				LOG_ERR(log::GetLastErrorAsString());
				wglDeleteContext(rc);
				ReleaseDC(tmp_window, dc);
				DestroyWindow(tmp_window);
				ControlWin::unregisterClass("OPENGL21TEMP");
				return -1;
			}

			glewExperimental = true;

			if (glewInit() != GLEW_OK)
			{
				LOG_ERR("Glew init failed");

				wglMakeCurrent(0, 0);
				wglDeleteContext(rc);
				ReleaseDC(tmp_window, dc);
				DestroyWindow(tmp_window);
				ControlWin::unregisterClass("OPENGL21TEMP");
				return -1;
			}

			wglMakeCurrent(0, 0);
			wglDeleteContext(rc);
			ReleaseDC(tmp_window, dc);
			DestroyWindow(tmp_window);
			ControlWin::unregisterClass("OPENGL21TEMP");

			dc = GetDC(window);
			pf = 0;

			if (!glewIsSupported("GL_VERSION_2_1"))
			{
				LOG_ERR("GL_VERSION 2.1 is not supported");
				ReleaseDC(window, dc);
				return -1;
			}

			const int dc_attributes[] =
			{
				WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
				WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
				WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
				WGL_SWAP_METHOD_ARB, WGL_SWAP_EXCHANGE_ARB,
				WGL_COLOR_BITS_ARB, 24,
				WGL_ALPHA_BITS_ARB, 8,
				WGL_DEPTH_BITS_ARB, 24,
				WGL_STENCIL_BITS_ARB, 8,
				WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
				WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
				WGL_SAMPLES_ARB, 8,
				0
			};

			const int rc_attributes[] =
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, 2,
				WGL_CONTEXT_MINOR_VERSION_ARB, 1,
				WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
				0
			};

			unsigned int pfc = 0;

			if (wglChoosePixelFormatARB(dc, dc_attributes, nullptr, 1, &pf, &pfc) == -1)
			{
				LOG_ERR("Pixel format invalid");
				ReleaseDC(window, dc);
				return - 1;
			}

			if (!SetPixelFormat(dc, pf, &pfd))
			{
				LOG_ERR("Setting pixel format error");
				ReleaseDC(window, dc);
				return -1;
			}

			rc = wglCreateContextAttribsARB(dc, 0, rc_attributes);
			if (rc == 0)
			{
				LOG_ERR("Creating RC error");
				ReleaseDC(window, dc);
				return -1;
			}

			if (!wglMakeCurrent(dc, rc))
			{
				LOG_ERR("Setting context error");
				ReleaseDC(window, dc);
				return -1;
			}

			ReleaseDC(window, dc);
			break;
		}

		case WM_PAINT:
		{
			std::cout << "Panel WM_PAINT" << std::endl;
			/*
			PAINTSTRUCT ps;
			HDC dc = BeginPaint(window, &ps);

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glLineWidth(2.0f);
			glBegin(GL_LINES);
			const double step = 0.01;
			for (double x = -1.0; x < 1.0; x += step)
			{
				glVertex2d(x, 0.25 * sin(4.0 * x)); x += step;
				glVertex2d(x, 0.25 * sin(4.0 * x)); x -= step;
			}
			glEnd();

			SwapBuffers(dc);
			EndPaint(window, &ps);
			*/
			if(scene != nullptr)scene->display();

			new_event.type = event::EventType::Repaint;
			break;
		}

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
			LOG_INF("Panel WM_DESTROY - GL termi");

			HGLRC rc = wglGetCurrentContext();
			wglMakeCurrent(0, 0);
			if (!wglDeleteContext(rc))
			{
				LOG_ERR("GL termi failed." << log::GetLastErrorAsString());
			}

			break;
		}

		case WM_SIZE:
		{
			new_event.type = event::EventType::Resize;
			unsigned int width = static_cast<unsigned int>(LOWORD(lparam));
			unsigned int height = static_cast<unsigned int>(HIWORD(lparam));
			setSize(width, height);
			glViewport(0, 0, width, height);
			break;
		}
		}

		if (new_event.type != event::EventType::None)handleEvent(new_event);

		return DefWindowProcA(window, message, wparam, lparam);
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