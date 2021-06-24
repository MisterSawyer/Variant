#pragma once
#include <vector>
#include <GLM/glm.hpp>

namespace vrt::render
{
	class Mesh
	{
	public:
		virtual ~Mesh();

		virtual void draw();
	protected:
		unsigned int vao, vbo, ebo;
		std::vector <glm::vec3> positions;
		std::vector <glm::vec3> normals;
		std::vector <glm::vec2> uvs;
	};
}