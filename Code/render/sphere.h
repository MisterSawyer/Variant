#pragma once

#pragma once
#include "mesh.h"
#include <GL/glew.h>

namespace vrt::render
{
	class SphereMesh : public Mesh
	{
	public:
		SphereMesh();
		virtual void draw() override;

	private:
		std::vector <GLuint> indices;
	};
}
