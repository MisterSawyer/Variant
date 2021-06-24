#include "window-blueprint.h"

namespace vrt::gui
{
	WindowBlueprint::WindowBlueprint()
		: ControlBlueprint()
	{
		control_class = "MAINWINDOW";
	}
}