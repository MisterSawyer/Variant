#pragma once
#include <string>
#include <vector>

#include "atom.h"

namespace vrt::data
{
	class PDB
	{
	private:
		std::string header;
		std::string title;
		std::vector<std::string> authors;
	};
}