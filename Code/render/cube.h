#pragma once
#include "mesh.h"

namespace vrt::render
{
	class CubeMesh : public Mesh
	{
	public:
		CubeMesh();

		void draw() override;
	};
}
