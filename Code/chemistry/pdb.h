#pragma once
#include <string>
#include <vector>
#include <map>
#include <chrono>

#include <GLM/glm.hpp>

#include "atom.h"

namespace vrt::data
{
	class PDB
	{
	public:
		bool loadFromFile(const std::string & filename);

		const std::vector<chemistry::Atom>& getAtoms()
		{
			return atoms;
		}


	private:
		struct COMPND
		{
			std::string MOLECULE;
			std::vector<std::string> CHAINS;
			std::string FRAGMENT;
			std::vector<std::string> SYNONYM;
			std::vector<unsigned int> EC;
			bool ENGINEERED; // TODO  w sumie nie wiem czy bool
			bool MUTATION; //TODO w sumie nie wiem czy bool
			std::string OTHER_DETAILS;
		};

		struct SOURCE
		{
			//TODO SYNTHETIC
			//TODO FRAGMENT                             
			std::string ORGANISM_SCIENTIFIC;
			std::string ORGANISM_COMMON;
			unsigned int ORGANISM_TAXID; //TODO sprawdzic czy musi byc liczb¹
			//STRAIN
			//VARIANT
			//CELL_LINE
			//ATCC
			//ORGAN
			//TISSUE
			//CELL
			//ORGANELLE
			//SECRETION
			//CELLULAR_LOCATION
			//PLASMID
			//GENE
			std::string EXPRESSION_SYSTEM;
			std::string EXPRESSION_SYSTEM_COMMON;
			unsigned int EXPRESSION_SYSTEM_TAXID;
			//EXPRESSION_SYSTEM_STRAIN
			//EXPRESSION_SYSTEM_VARIANT
			std::string EXPRESSION_SYSTEM_CELL_LINE;
			//EXPRESSION_SYSTEM_ATCC_NUMBER
			//EXPRESSION_SYSTEM_ORGAN
			//EXPRESSION_SYSTEM_TISSUE
			//EXPRESSION_SYSTEM_CELL
			//EXPRESSION_SYSTEM_ORGANELLE
			//EXPRESSION_SYSTEM_CELLULAR_LOCATION
			std::string EXPRESSION_SYSTEM_VECTOR_TYPE;
			std::string EXPRESSION_SYSTEM_VECTOR;
			//EXPRESSION_SYSTEM_PLASMID
			//EXPRESSION_SYSTEM_GENE
			std::string OTHER_DETAILS;
		};

		struct REVDAT
		{
			std::time_t date;
			bool initial;
		};

		std::string header;
		std::string title;
		std::vector<std::string> authors;
		std::map<unsigned int, COMPND> compounds;
		std::map<unsigned int, SOURCE> sources;
		std::vector<std::string> key_words;
		std::string experiment_info;
		std::map<unsigned int, REVDAT> revdat;

		std::vector<chemistry::Atom> atoms;


	};
}