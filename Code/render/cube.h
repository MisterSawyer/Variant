#pragma once
#include "mesh.h"
#include <GL/glew.h>

namespace vrt::render
{
	class CubeMesh : public Mesh
	{
	public:
		CubeMesh();
		virtual void draw() override; 

	private:
		std::vector <GLuint> indices;
	};
}
