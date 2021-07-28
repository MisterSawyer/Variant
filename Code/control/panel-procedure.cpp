#include "panel-win.h"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <windowsx.h>
#include "../log/log.h"


namespace vrt::gui
{
	WNDCLASSEX createSettingTempWindow()
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

		return class_type;
	}

	PIXELFORMATDESCRIPTOR createSettingPixelFormatDescriptor()
	{
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

		return pfd;
	}


	LRESULT __stdcall PanelWin::procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
	{
		event::Event new_event;

		switch (message)
		{
		case WM_CREATE:
		{

			WNDCLASSEX class_type = createSettingTempWindow();
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

			PIXELFORMATDESCRIPTOR pfd = createSettingPixelFormatDescriptor();

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
				WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
				0
			};

			unsigned int pfc = 0;

			if (wglChoosePixelFormatARB(dc, dc_attributes, nullptr, 1, &pf, &pfc) == -1)
			{
				LOG_ERR("Pixel format invalid");
				ReleaseDC(window, dc);
				return -1;
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

			LOG_INF("OpenGL context created sucessfully");

			glEnable(GL_DEPTH_TEST);
			ReleaseDC(window, dc);
			device_context_handle = dc;
			render_context_handle = rc;

			new_event.type = event::EventType::Invalidated;

			SetTimer(window, 1, 1, (TIMERPROC)NULL);

			break;
		}

		case WM_PAINT:
		{
			render();
			new_event.type = event::EventType::Repainted;
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
				//TODO event tez do dziecka chyba 
				break;
			}
			}
			break;
		}

		case WM_DESTROY:
		{
			KillTimer(window, 0);
			new_event.type = event::EventType::Destroy;
			LOG_INF("Panel WM_DESTROY - OpenGL termination");

			HGLRC rc = wglGetCurrentContext();
			wglMakeCurrent(0, 0);
			if (!wglDeleteContext(rc))
			{
				LOG_ERR("OpenGL terminatioon failed." << log::GetLastErrorAsString());
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
			camera.setViewportSize(getSize());
			break;
		}
		case WM_TIMER:
		{
			//getCamera().rotateHorizontal(0.01);
			
			break;
		}

		case WM_MOUSEMOVE:
		{
			float scale = 0.3;

			float cursor_x = static_cast<float>(GET_X_LPARAM(lparam));
			float cursor_y = static_cast<float>(GET_Y_LPARAM(lparam));

			if (wparam == MK_LBUTTON)
			{
				camera.rotateVertical(scale * (cursor_y - mouse_position.y));
				camera.rotateHorizontal(scale * (cursor_x - mouse_position.x));
			}
			if (wparam == MK_RBUTTON)
			{
				camera.moveCamera(scale * (mouse_position.x - cursor_x), scale * (mouse_position.y - cursor_y));

			}

			mouse_position = glm::vec2(cursor_x, cursor_y);
			new_event.type = event::EventType::Invalidated;
			break;
		}
		case WM_MOUSEWHEEL:
		{
			float scale = 0.3;
			float delta = static_cast<float>(GET_WHEEL_DELTA_WPARAM(wparam));
			camera.zoom(scale* -delta);

			new_event.type = event::EventType::Invalidated;
			break;
		}

		}

		if (new_event.type != event::EventType::None)handleEvent(new_event);
		if (new_event.type != event::EventType::None)propagateEvent(new_event);

		return DefWindowProcA(window, message, wparam, lparam);
	}
}