#include "model.h"
#include "../log/log.h"

namespace vrt::render
{
	Model::Model(Mesh* mesh_info)
	{
		mesh = mesh_info;
	}

	Model::Model(Model && obj)noexcept
		: Transformable(std::move(obj))
	{
		mesh = std::move(obj.mesh);
		color = std::move(obj.color);
	}

	Model& Model::operator=(const Model& obj)
	{
		if (this == &obj)
		{
			LOG_WAR("Self assigment");
			return *this;
		}

		this->Transformable::operator=(obj);
		mesh = obj.mesh;
		color = obj.color;

		return *this;
	}

	Model& Model::operator=(Model&& obj)noexcept
	{
		if (this == &obj)
		{
			LOG_WAR("Self assigment");
			return *this;
		}

		this->Transformable::operator=(std::move(obj));
		mesh = std::move(obj.mesh);
		color = std::move(obj.color);

		return *this;
	}

	Model & Model::operator=(const Transformable& tr)
	{
		this->Transformable::operator=(tr);
		return *this;
	}

	Model& Model::operator=(Transformable&& obj)noexcept
	{
		this->Transformable::operator=(std::move(obj));
		return *this;
	}

	void Model::setColor(const glm::vec4& color_arg)
	{
		color = color_arg;
	}

	void Model::setColor(const Color& color_arg)
	{
		color = mapToRGBA(color_arg);
	}

	glm::vec4 Model::getColor()const
	{
		return color;
	}

	void Model::display()
	{
		if (mesh != nullptr)mesh->draw();
		else LOG_ERR("Empty mesh data");
	}
}