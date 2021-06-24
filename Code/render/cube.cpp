#include "../Code/log/log.h"

#include "cube.h"
#include <GL/glew.h>
#include <GLM/glm.hpp>

namespace vrt::render
{

	CubeMesh::CubeMesh()
	{


		positions.push_back(glm::vec3(-0.5f, -0.5f, 0.5f)); normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f)); uvs.push_back(glm::vec2(0.0f, 0.0f));
		positions.push_back(glm::vec3(-0.5f, 0.5f, 0.5f)); normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f)); uvs.push_back(glm::vec2(0.0f, 1.0f));
		positions.push_back(glm::vec3(0.5f, -0.5f, 0.5f)); normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f)); uvs.push_back(glm::vec2(1.0f, 0.0f));
		positions.push_back(glm::vec3(0.5f, 0.5f, 0.5f)); normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f)); uvs.push_back(glm::vec2(1.0f, 1.0f));

		positions.push_back(glm::vec3(0.5f, -0.5f, 0.5f)); normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f)); uvs.push_back(glm::vec2(0.0f, 0.0f));
		positions.push_back(glm::vec3(0.5f, 0.5f, 0.5f)); normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f)); uvs.push_back(glm::vec2(0.0f, 1.0f));
		positions.push_back(glm::vec3(0.5f, -0.5f, -0.5f)); normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f)); uvs.push_back(glm::vec2(1.0f, 0.0f));
		positions.push_back(glm::vec3(0.5f, 0.5f, -0.5f)); normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f)); uvs.push_back(glm::vec2(1.0f, 1.0f));

		positions.push_back(glm::vec3(0.5f, -0.5f, -0.5f)); normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f)); uvs.push_back(glm::vec2(0.0f, 0.0f));
		positions.push_back(glm::vec3(0.5f, 0.5f, -0.5f)); normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f)); uvs.push_back(glm::vec2(0.0f, 1.0f));
		positions.push_back(glm::vec3(-0.5f, -0.5f, -0.5f)); normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f)); uvs.push_back(glm::vec2(1.0f, 0.0f));
		positions.push_back(glm::vec3(-0.5f, 0.5f, -0.5f)); normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f)); uvs.push_back(glm::vec2(1.0f, 1.0f));

		positions.push_back(glm::vec3(-0.5f, -0.5f, -0.5f)); normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f)); uvs.push_back(glm::vec2(0.0f, 0.0f));
		positions.push_back(glm::vec3(-0.5f, 0.5f, -0.5f)); normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f)); uvs.push_back(glm::vec2(0.0f, 1.0f));
		positions.push_back(glm::vec3(-0.5f, -0.5f, 0.5f)); normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f)); uvs.push_back(glm::vec2(1.0f, 0.0f));
		positions.push_back(glm::vec3(-0.5f, 0.5f, 0.5f)); normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f)); uvs.push_back(glm::vec2(1.0f, 1.0f));

		positions.push_back(glm::vec3(-0.5f, 0.5f, 0.5f)); normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f)); uvs.push_back(glm::vec2(0.0f, 0.0f));
		positions.push_back(glm::vec3(-0.5f, 0.5f, -0.5f)); normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f)); uvs.push_back(glm::vec2(0.0f, 1.0f));
		positions.push_back(glm::vec3(0.5f, 0.5f, 0.5f)); normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f)); uvs.push_back(glm::vec2(1.0f, 0.0f));
		positions.push_back(glm::vec3(0.5f, 0.5f, -0.5f)); normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f)); uvs.push_back(glm::vec2(1.0f, 1.0f));

		positions.push_back(glm::vec3(-0.5f, -0.5f, -0.5f)); normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f)); uvs.push_back(glm::vec2(0.0f, 0.0f));
		positions.push_back(glm::vec3(-0.5f, -0.5f, 0.5f)); normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f)); uvs.push_back(glm::vec2(0.0f, 1.0f));
		positions.push_back(glm::vec3(0.5f, -0.5f, -0.5f)); normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f)); uvs.push_back(glm::vec2(1.0f, 0.0f));
		positions.push_back(glm::vec3(0.5f, -0.5f, 0.5f)); normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f)); uvs.push_back(glm::vec2(1.0f, 1.0f));

		const size_t positions_size = positions.size() * sizeof(glm::vec3);
		const size_t normals_size = normals.size() * sizeof(glm::vec3);
		const size_t uvs_size = uvs.size() * sizeof(glm::vec2);

		std::vector <GLuint> indices;

		indices.push_back(0); indices.push_back(1); indices.push_back(2); indices.push_back(2); indices.push_back(1); indices.push_back(3);
		indices.push_back(4); indices.push_back(5); indices.push_back(6); indices.push_back(6); indices.push_back(5); indices.push_back(7);
		indices.push_back(8); indices.push_back(9); indices.push_back(10); indices.push_back(10); indices.push_back(9); indices.push_back(11);
		indices.push_back(12); indices.push_back(13); indices.push_back(14); indices.push_back(14); indices.push_back(13); indices.push_back(15);
		indices.push_back(16); indices.push_back(17); indices.push_back(18); indices.push_back(18); indices.push_back(17); indices.push_back(19);
		indices.push_back(20); indices.push_back(21); indices.push_back(22); indices.push_back(22); indices.push_back(21); indices.push_back(23);

		const size_t indices_size = indices.size() * sizeof(GLuint);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, positions_size + normals_size + uvs_size, nullptr, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, positions_size, (void*)&positions[0]);
		glBufferSubData(GL_ARRAY_BUFFER, positions_size, normals_size, (void*)&normals[0]);
		glBufferSubData(GL_ARRAY_BUFFER, positions_size + normals_size, uvs_size, (void*)&uvs[0]);

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, (void*)&indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)(positions_size));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(positions_size + normals_size));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}



}
