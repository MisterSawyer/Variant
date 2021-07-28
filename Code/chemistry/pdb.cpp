#include "pdb.h"
#include <fstream>
#include "../Code/log/log.h"


namespace vrt::data
{
	bool PDB::loadFromFile(const std::string& filename)
	{
		std::ifstream file;
		file.open(filename);

		if (!file.good())
		{
			LOG_ERR("Cannot open "<<filename);
			file.close();
			return false;
		}

		for (std::string line; std::getline(file, line); )
		{
			if (line.rfind("ATOM", 0) == 0)
			{
				chemistry::Atom atom;
				atom.ID = std::stof(line.substr(6, 5)); // 7 - 11
				atom.name = line.substr(12, 4); // 13 - 16
				atom.alt_loc = line[16]; // 17
				atom.reside_name = line.substr(17, 3); // 18 - 20
				atom.chain = line[21]; // 22
				atom.residue_id = std::stof(line.substr(22, 4)); // 23 - 26
				atom.icode = line[26]; // 27
				atom.position.x = std::stof(line.substr(30, 8)); // 31 - 38
				atom.position.y = std::stof(line.substr(38, 8)); // 39 - 46
				atom.position.z = std::stof(line.substr(46, 8)); // 47 - 54
				atom.occupancy = std::stof(line.substr(54, 6)); //55 - 60
				atom.temp = std::stof(line.substr(60, 6)); //61 - 66
				atom.element = line.substr(76, 2); // 77 - 78 
				atom.charge = line.substr(78, 2); //79 - 80

				if (atom.alt_loc == 32)atom.alt_loc = 0;
				if (atom.chain == 32)atom.chain = 0;
				if (atom.icode == 32)atom.icode = 0;

				atom.name.erase(remove(atom.name.begin(), atom.name.end(), ' '), atom.name.end());
				atom.reside_name.erase(remove(atom.reside_name.begin(), atom.reside_name.end(), ' '), atom.reside_name.end());
				atom.element.erase(remove(atom.element.begin(), atom.element.end(), ' '), atom.element.end());
				atom.charge.erase(remove(atom.charge.begin(), atom.charge.end(), ' '), atom.charge.end());

				atoms.push_back(std::move(atom));
			}
		}


		file.close();
		return true;
	}
}
