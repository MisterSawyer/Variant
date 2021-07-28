#pragma once
#include "mesh.h"
#include <GL/glew.h>

namespace vrt::render
{
	class CylinderMesh : public Mesh
	{
	public:
		CylinderMesh();
		virtual void draw() override;

	private:
		std::vector <GLuint> indices;
	};
}
