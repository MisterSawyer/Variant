#pragma once
#include "model.h"
#include "observer.h"
#include "shader.h"

namespace vrt::render
{
	class Scene : public utils::Subject, public utils::Observer
	{
	public:
		void clear();
		void addModel(Model* model);
		void deleteModel(Model* model);
		void setShader(Shader * shader);
		void display(const glm::mat4 & camera);
	protected:
		void update(const std::string& message_from_subject) override;
	private:
		glm::mat4 camera;
		Shader* used_shader;
		std::list<Model *> models;
	};
}
