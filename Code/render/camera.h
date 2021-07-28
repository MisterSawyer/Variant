#pragma once
#include <GLM/glm.hpp>

namespace vrt::render
{
	class Camera
	{
	public:
		Camera();

		void setTarget(glm::vec3 position);
		void setTarget(float x, float y, float z);

		void setViewportSize(glm::vec2 viewport);

		void rotateVertical(float angle);
		void rotateHorizontal(float angle);

		void moveTarget(glm::vec3 vecXYZ);
		void moveTarget(float X, float Y, float Z);

		void moveCamera(glm::vec2 vecXY);
		void moveCamera(float X, float Y);

		void setDistance(float distance);

		void zoom(float value);

		glm::mat4 getMatrix();

		glm::vec3 getTarget()const;

	private:
		glm::mat4 camera_matrix;

		float FOV; // radians
		glm::vec2 viewport_size;
		glm::vec3 camera_pos;

		glm::vec3 camera_origin;
		glm::vec3 camera_up;

		float radius;
		float angle_v;
		float angle_h;
	};
}