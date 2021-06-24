#pragma once

#include "control-style.h"
#include <string>

#include <GLM/glm.hpp>

namespace vrt::gui
{
	class ControlBlueprint
	{
	public:
		std::string name;
		glm::ivec2 position;
		glm::ivec2 size;
		ControlStyle style;

		const std::string& getControlClassName() const;
	protected:
		ControlBlueprint() = default;

		std::string control_class;
	private:

	};
}