#include "scene.h"
#include "../Code/log/log.h"


namespace vrt::render
{
	void Scene::clear()
	{
		models.clear();
	}

	void Scene::addModel(Model* model)
	{
		model->attach(this);
		models.push_back(model);
		notify("scene changed");
	}

	void Scene::deleteModel(Model* model)
	{
		models.remove(model);
		notify("scene changed");
	}

	void Scene::update(const std::string& message_from_subject)
	{
		notify("object on scene changed");
	}

	void Scene::display(const glm::mat4 & camera)
	{
		if (used_shader == nullptr)
		{
			LOG_ERR("Scene has empty shader - cannot display");
			return;
		}

		used_shader->use();
		
		for (auto & model : models)
		{
			used_shader->send(glm::vec3(20, -100, 300), "light_pos");
			used_shader->send(model->getMatrix(), "model");
			used_shader->send(camera, "VP");
			used_shader->send(model->getColor(), "Color");
			model->display();
		}
	}

	void Scene::setShader(Shader* shader)
	{
		used_shader = shader;
	}
}