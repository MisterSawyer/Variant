#pragma once
#include "mesh.h"
#include "../transformable/transformable.h"

namespace vrt::render
{
	class Model : public Transformable
	{
	public:
		Mesh* model;
	};
}