#include "colors.h"

namespace vrt::render
{
	/*
	White for hydrogen.
	Black for carbon.
	Blue for nitrogen.
	Red for oxygen.
	Deep yellow for sulfur.
	Purple for phosphorus.
	Light, medium, medium dark, and dark green for the halogens(F, Cl, Br, I)
	Silver for metals(Co, Fe, Ni, Cu)
	*/

	glm::vec4 mapToRGBA(const Color& color)
	{
		switch (color)
		{
		case Color::White: return glm::vec4(1, 1, 1, 1);
		case Color::Black: return glm::vec4(0, 0, 0, 1);
		case Color::DarkYellow: return glm::vec4(0.6, 0.52, 0.04, 1);
		case Color::Purple: return glm::vec4(0.5, 0, 0.5, 1);
		case Color::LightGray: return glm::vec4(0.5, 0.5, 0.5, 1);
		case Color::MediumGray: return glm::vec4(0.5, 0.5, 0.5, 1);
		case Color::DarkGray: return glm::vec4(0.25, 0.25, 0.25, 1);

		case Color::Red: return glm::vec4(1, 0, 0, 1);
		case Color::Green: return glm::vec4(0, 1, 0, 1);
		case Color::Blue: return glm::vec4(0, 0, 1, 1);


		default: return glm::vec4(1, 1, 1, 1);
		}
	}
}