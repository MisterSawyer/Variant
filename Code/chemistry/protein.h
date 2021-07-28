#pragma once

#include "atom.h"
#include "bond.h"
#include "../Code/render/model.h"
#include "../Code/chemistry/pdb.h"

namespace vrt::chemistry
{
	class ProteinModel
	{

		ProteinModel(const data::PDB & file);
		void render();
	private:
		std::vector<vrt::render::Model> atoms_models;
	};
}