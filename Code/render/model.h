#pragma once
#include "mesh.h"
#include "../transformable/transformable.h"
#include "colors.h"

namespace vrt::render
{
	class Model : public Transformable
	{
	public:
		explicit Model(Mesh * mesh_info);
		Model(Model&&)noexcept;

		Model& operator=(const Model&);
		Model& operator=(Model&&)noexcept;
		Model& operator=(const Transformable&);
		Model& operator=(Transformable&&)noexcept;

		void display();
		
		void setColor(const glm::vec4 & color);
		void setColor(const Color & color);

		glm::vec4 getColor()const;

	private:
		Mesh* mesh;
		glm::vec4 color;
	};
}