#pragma once

#include <optional>

#include "atom-types.h"

namespace vrt::atom
{
	class Atom
	{
	public:

	private:
		unsigned int ID_;
		std::optional<AtomInfo> info_;
	};
}