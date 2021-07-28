#pragma once


#include <vector>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtx/quaternion.hpp>
#include "../Code/render/observer.h"

namespace vrt {

	class Transformable: public utils::Subject
	{
	public:
		Transformable();
		explicit Transformable(glm::vec3 position);
		explicit Transformable(float pos_x, float pos_y, float pos_z);

		Transformable(const Transformable&);
		Transformable(Transformable&&)noexcept;
		Transformable& operator=(const Transformable&);
		Transformable& operator=(Transformable&&)noexcept;

		virtual ~Transformable() = default;

		void setPosition(glm::vec3 position);
		void setPosition(float x, float y, float z);
		void setPositionX(float x);
		void setPositionY(float y);
		void setPositionZ(float z);

		void setRotation(glm::vec3 rotation);
		void setRotation(float x, float y, float z);
		void setRotationX(float x);
		void setRotationY(float y);
		void setRotationZ(float z);

		void setScale(glm::vec3 scale);
		void setScale(float x, float y, float z);
		void setScaleX(float x);
		void setScaleY(float y);
		void setScaleZ(float z);

		glm::vec3 getPosition() const;
		glm::vec3 getRotation() const;
		glm::vec3 getScale() const;

		float getPositionX() const;
		float getPositionY() const;
		float getPositionZ() const;

		float getRotationX() const;
		float getRotationY() const;
		float getRotationZ() const;

		float getScaleX() const;
		float getScaleY() const;
		float getScaleZ() const;

		glm::mat4 getMatrix();

	private:
		void update();

		glm::mat4 matrix_;
		glm::vec3 position_, rotation_, scale_;
		bool to_update_;
	};
}
