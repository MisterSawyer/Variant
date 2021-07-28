//#include <Windows.h>

#include "../Code/control/gui-win-factory.h"
#include <GL/glew.h>
#include <GL/wglew.h>

#include <math.h>

#include "../Code/log/log.h"

#include "../Code/view/view.h"
#include "../Code/render/shader.h"

#include "../Code/render/cube.h"
#include "../Code/render/sphere.h"
#include "../Code/render/cylinder.h"

#include "../Code/chemistry/pdb.h"

 // Windows.h


//LRESULT __stdcall windowProcedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
//LRESULT __stdcall panelProcedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
//void timerProcedure(HWND window, UINT message, UINT_PTR id, DWORD time);
/*
bool registerWindowClasses(HINSTANCE instance)
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instance;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIconSm = LoadIcon(0, IDI_APPLICATION);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	wc.lpfnWndProc = windowProcedure;
	wc.lpszClassName = "MAINWINDOW";
	wc.lpszMenuName = nullptr;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	bool success = RegisterClassExA(&wc);

	wc.hCursor = LoadCursor(0, IDC_HAND);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wc.lpfnWndProc = panelProcedure;
	wc.lpszClassName = "OPENGLPANEL";
	wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

	success = success && RegisterClassExA(&wc);

	return success;
}
*/

//using namespace Gdiplus;

vrt::Transformable calculateTransformation(const glm::vec3 & A, const glm::vec3 & B)
{
	vrt::Transformable tr;
	double d = glm::distance(A, B);
	tr.setScaleX(0.1);
	tr.setScaleZ(0.1);
	tr.setScaleY(d);
	tr.setPosition(A);
	
	double k = glm::degrees(glm::atan((A.y - B.y), (A.x - B.x)));
	tr.setRotationZ(k);

	k = glm::degrees(glm::atan((A.z - B.z), (A.x - B.x)));
	tr.setRotationY(k);

	return tr;
}


int main()
{
	int cmdshow = SW_SHOW;

	vrt::gui::ButtonBlueprint button_blueprint;
	vrt::gui::WindowBlueprint window_blueprint;
	vrt::gui::PanelBlueprint panel_blueprint;

	window_blueprint.position.x = 500;
	window_blueprint.position.y = 200;
	window_blueprint.size.x = 800;
	window_blueprint.size.y = 800;
	window_blueprint.name = "window";

	button_blueprint.position.x = 120;
	button_blueprint.position.y = 100;
	button_blueprint.size.x = 200;
	button_blueprint.size.y = 50;
	button_blueprint.name = "button";

	panel_blueprint.position.x = 20;
	panel_blueprint.position.y = 20;
	panel_blueprint.size.x = 760;
	panel_blueprint.size.y = 760;
	panel_blueprint.name = "panel";

	std::shared_ptr<vrt::gui::GUIWinFactory> factory = std::make_shared<vrt::gui::GUIWinFactory>();

	vrt::gui::View view0(factory);
	vrt::gui::WindowInterface * window = view0.createWindow(window_blueprint);
	auto btn = view0.createButton(button_blueprint, window, 1);
	auto panel = view0.createPanel(panel_blueprint, window, 2);
	window->show(1);
	panel->show(1);


	vrt::render::Shader sh;
	sh.loadFromFiles("../data/shaders/vertex.vert", "../data/shaders/fragment.frag");


	vrt::render::Scene sc;
	sc.setShader(&sh);

	vrt::render::CubeMesh cuber_mesh;
	vrt::render::SphereMesh sphere;
	vrt::render::CylinderMesh cylinder;

	vrt::data::PDB file;
	file.loadFromFile("../data/pdb/1iyj.pdb");
	std::vector<std::unique_ptr<vrt::render::Model>> models;

	vrt::render::Model camera_center(&sphere);
	camera_center.setScale(0.1, 0.1, 0.1);
	camera_center.setColor(glm::vec4(1, 1, 1, 0.25));

	float scale = 1;

	for (unsigned int i=0; i< file.getAtoms().size(); i++)
	{
		models.push_back(std::make_unique< vrt::render::Model>(vrt::render::Model(&sphere)));
		models.back()->setPosition(file.getAtoms()[i].position);
		

		if (file.getAtoms()[i].element == "C")
		{
			models.back()->setScale(scale *1.7, scale*1.7, scale * 1.7);
			models.back()->setColor(vrt::render::Color::DarkGray);
		}
		if (file.getAtoms()[i].element == "H")
		{
			models.back()->setScale(scale * 1.2, scale * 1.2, scale * 1.2);
			models.back()->setColor(vrt::render::Color::White);
		}
		if (file.getAtoms()[i].element == "N")
		{
			models.back()->setScale(scale * 1.55, scale * 1.55, scale * 1.55);
			models.back()->setColor(vrt::render::Color::Blue);
		}
		if (file.getAtoms()[i].element == "O")
		{
			models.back()->setScale(scale * 1.52, scale * 1.52, scale * 1.52);
			models.back()->setColor(vrt::render::Color::Red);
		}

		if (file.getAtoms()[i].element == "S")
		{
			models.back()->setScale(scale * 1.8, scale * 1.8, scale * 1.8);
			models.back()->setColor(vrt::render::Color::DarkYellow);
		}


		sc.addModel(models.back().get());
	}

	panel->getCamera().setTarget(0, 20, 0);
	panel->getCamera().setDistance(50);
	sc.addModel(&camera_center);

	panel->setScene(&sc);

	MSG msgcontainer = { 0 };
	while (GetMessageA(&msgcontainer, 0, 0, 0) > 0)
	{
		TranslateMessage(&msgcontainer);
		DispatchMessageA(&msgcontainer);
		//
		camera_center.setPosition(panel->getCamera().getTarget());
	}



	//vrt::gui::ButtonInterface* btn = factory.createButton(blueprint);


	//delete btn;

	/*
	if (!registerWindowClasses(instance))
	{
		MessageBox(0, "Registering window classes failed.", "Error", MB_ICONERROR | MB_OK);
		return -1;
	}

	HWND mainwindow = CreateWindowExA(0, "MAINWINDOW", "OpenGL Panel Test", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1200, 600, 0, 0, instance, nullptr);
	if (mainwindow == 0)
	{
		MessageBox(0, "Creating window failed.", "Error", MB_ICONERROR | MB_OK);
		return -1;
	}
	ShowWindow(mainwindow, cmdshow);
	UpdateWindow(mainwindow);

	MSG msgcontainer = { 0 };
	while (GetMessage(&msgcontainer, 0, 0, 0) > 0)
	{
		TranslateMessage(&msgcontainer);
		DispatchMessage(&msgcontainer);
	}
	

	return static_cast<int>(msgcontainer.wParam);
	*/



	return 0;
}
/*
LRESULT __stdcall windowProcedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		MOUSE_L_PRESSED = TRUE;
		break;
	}

	case WM_LBUTTONUP:
	{
		MOUSE_L_PRESSED = FALSE;
		break;
	}

	case WM_COMMAND:
	{
		if (HIWORD(wparam) == BN_CLICKED)
		{
			switch (LOWORD(wparam))
			{
			case 1:
			{
				TRIANGLE_ROTATION += 30.0f;
				break;
			}

			case 2:
			{
				TRIANGLE_ROTATION -= 30.0f;
				break;
			}

			case 3:
			{
				TRIANGLE_ROTATION = 0.0f;
				break;
			}
			}
		}
		break;
	}

	case WM_CREATE:
	{
		HWND openglpanel = CreateWindowExA(0, "OPENGLPANEL", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 10, 800, 400, window, 0, INSTANCE_HANDLE, nullptr);
		if (openglpanel == 0) return -1;

		

		HWND leftbutton = CreateWindowEx(0, "BUTTON", "Rotate left", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 415, 128, 32, window, reinterpret_cast<HMENU>(1), INSTANCE_HANDLE, nullptr);
		if (leftbutton == 0) return -1;

		HWND rightbutton = CreateWindowEx(0, "BUTTON", "Rotate right", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 143, 415, 128, 32, window, reinterpret_cast<HMENU>(2), INSTANCE_HANDLE, nullptr);
		if (rightbutton == 0) return -1;

		HWND resetbutton = CreateWindowEx(0, "BUTTON", "Reset", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 276, 415, 128, 32, window, reinterpret_cast<HMENU>(3), INSTANCE_HANDLE, nullptr);
		if (resetbutton == 0) return -1;



		return 0;
	}

	case WM_CLOSE:
	{
		DestroyWindow(window);
		break;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	}

	return DefWindowProcA(window, message, wparam, lparam);
}

LRESULT __stdcall panelProcedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		MOUSE_L_PRESSED = TRUE;
		GetCursorPos(&MOUSE_L_PRESSED_POINT);
		ScreenToClient(window, &MOUSE_L_PRESSED_POINT);
		break;
	}

	case WM_LBUTTONUP:
	{
		MOUSE_L_PRESSED = FALSE;
		TRIANGLE_ROTATION += TRIANGLE_ROTATION_DIFF;
		TRIANGLE_ROTATION_DIFF = 0.0f;
		break;
	}

	case WM_CREATE:
	{
		PIXELFORMATDESCRIPTOR pfd = { 0 };
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.cColorBits = 24;
		pfd.cAlphaBits = 8;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.iLayerType = PFD_MAIN_PLANE;

		HDC dc = GetDC(window);
		int pf = ChoosePixelFormat(dc, &pfd);
		if (!SetPixelFormat(dc, pf, &pfd))
		{
			MessageBox(window, "Setting pixel format failed.", "Error", MB_ICONERROR | MB_OK);
			return -1;
		}

		HGLRC rc = wglCreateContext(dc);
		if (rc == 0)
		{
			MessageBox(window, "Creating OpenGL context failed.", "Error", MB_ICONERROR | MB_OK);
			return -1;
		}

		if (!wglMakeCurrent(dc, rc))
		{
			MessageBox(window, "Making context current failed.", "Error", MB_ICONERROR | MB_OK);
			return -1;
		}

		RECT client;
		GetClientRect(window, &client);

		GLsizei width = static_cast<GLsizei>(client.right - client.left);
		GLsizei height = static_cast<GLsizei>(client.bottom - client.top);

		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-0.5 * static_cast<GLdouble>(width), 0.5 * static_cast<GLdouble>(width), -0.5 * static_cast<GLdouble>(height), 0.5 * static_cast<GLdouble>(height), 0.0f, 1.0f);
		glPointSize(8.0f);

		SetTimer(window, 3, 1, timerProcedure);

		return 0;
	}

	case WM_CLOSE:
	{
		KillTimer(window, 3);

		HDC dc = wglGetCurrentDC();
		HGLRC rc = wglGetCurrentContext();
		wglMakeCurrent(0, 0);

		wglDeleteContext(rc);
		ReleaseDC(window, dc);

		DestroyWindow(window);

		break;
	}
	}

	return DefWindowProc(window, message, wparam, lparam);
}

void timerProcedure(HWND window, UINT message, UINT_PTR id, DWORD time)
{
	POINT cursor;
	GetCursorPos(&cursor);
	ScreenToClient(window, &cursor);

	RECT client;
	GetClientRect(window, &client);
	LONG width = client.right - client.left;
	LONG height = client.bottom - client.top;

	float cursorx = static_cast<float>(cursor.x);
	float cursory = static_cast<float>(cursor.y);

	float cursorclickx = static_cast<float>(MOUSE_L_PRESSED_POINT.x);
	float cursorclicky = static_cast<float>(MOUSE_L_PRESSED_POINT.y);

	cursorx = cursorx - 0.5f * static_cast<float>(width);
	cursory = 0.5f * static_cast<float>(height) - cursory;

	cursorclickx = cursorclickx - 0.5f * static_cast<float>(width);
	cursorclicky = 0.5f * static_cast<float>(height) - cursorclicky;

	if (MOUSE_L_PRESSED)
	{
		TRIANGLE_ROTATION_DIFF = atan2f(cursory, cursorx) - atan2f(cursorclicky, cursorclickx);
		TRIANGLE_ROTATION_DIFF = TRIANGLE_ROTATION_DIFF * 180.0f / (float)M_PI;
	}

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glRotatef(TRIANGLE_ROTATION + TRIANGLE_ROTATION_DIFF, 0.0f, 0.0f, 1.0f);
	glScalef(200.0f, 200.0f, 1.0f);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.5f, -0.5f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.0f, 0.5f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.5f, -0.5f);
	glEnd();
	glPopMatrix();

	if (MOUSE_L_PRESSED)
	{
		glBegin(GL_POINTS);
		glColor3f(1.0f, 1.0f, 1.0f); glVertex2f(cursorclickx, cursorclicky);
		glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(cursorx, cursory);
		glEnd();
	}
	else
	{
		glBegin(GL_POINTS);
		glColor3f(1.0f, 1.0f, 1.0f); glVertex2f(cursorx, cursory);
		glEnd();
	}

	SwapBuffers(GetDC(window));
}
*/