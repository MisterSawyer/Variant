#pragma once
#include "model.h"
#include "observer.h"

namespace vrt::render
{
	class Scene : public utils::Subject
	{
	public:
		void clear();
		void addModel(Model* model);
		void deleteModel(Model* model);

		void display();

	private:
		std::vector<Model *> models;
	};
}
