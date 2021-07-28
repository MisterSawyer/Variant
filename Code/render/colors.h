#pragma once
#include <GLM/glm.hpp>

namespace vrt::render
{

	enum class Color
	{
		White, Black, Red, Green, Blue, DarkYellow, Purple, LightGray, MediumGray, DarkGray, LightGreen, MediumGreen, DarkGreen, Silver
	};

	glm::vec4 mapToRGBA(const Color & color); // to avoid singleton
}
