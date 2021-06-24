#pragma once

#include <unordered_map>

#include "bond.h"
#include "atom.h"

//algorithm st¹d
//https://jcheminf.biomedcentral.com/articles/10.1186/1758-2946-4-26

namespace vrt::atom
{
	class Model
	{
	public:
		bool loadFromFile();
		void generateBonds();
	private:
		std::unordered_map<unsigned int, Atom> atoms_;
		std::vector<Bond> bonds_;
	};
}
