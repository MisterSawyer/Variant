#pragma once
#include <string>


namespace vrt::chemistry
{

	enum class AtomType
	{
		UNKNOWN, H, C, N, O, F, P, S, Cl, Br, I
	};

	class AtomInfo
	{
	public:

	private:
		int max_connections; //-1 for unknown
		AtomType type;
	};

	bool loadAtomInfo(const std::string & file);

	const AtomInfo& getAtomInfo(const std::string & name);
	const AtomInfo& getAtomInfo(const AtomType & type);
}