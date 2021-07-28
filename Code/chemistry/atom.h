#pragma once

#include <optional>
#include <array>
#include "residue-types.h"
#include "atom-types.h"
#include <GLM/glm.hpp>

namespace vrt::chemistry
{
	struct Atom
	{
		unsigned int ID;

		std::string name;
		char alt_loc;
		char chain;
		unsigned int residue_id;
		char icode;
		float occupancy;
		float temp;

		std::string reside_name; //TODO residue type 
		glm::vec3 position;
		std::string element;
		std::string charge;
		//TODO AtomInfo * type;
	};
}