#include "mesh.h"
#include <GL/glew.h>

namespace vrt::render
{
	Mesh::~Mesh()
	{
		if (ebo != 0)
		{
			glDeleteBuffers(1, &ebo);
			ebo = 0;
		}

		if (vbo != 0)
		{
			glDeleteBuffers(1, &vbo);
			vbo = 0;
		}

		if (vao != 0)
		{
			glDeleteVertexArrays(1, &vao);
			vao = 0;
		}
	}

	void Mesh::draw()
	{
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}