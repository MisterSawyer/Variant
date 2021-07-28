#include "camera.h"
#include <GLM/gtc/matrix_transform.hpp>

namespace vrt::render
{
	Camera::Camera()
	{
		camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
		FOV = glm::radians(45.0f);
		radius = 1.0f;
		angle_h = 0;
		angle_v = 3.14;
		camera_pos = glm::vec3(0, 1, 0);
		camera_origin = glm::vec3(0, 0, 0);
	}

	void Camera::zoom(float value)
	{
		radius += value;
	}

	glm::mat4 Camera::getMatrix()
	{
		if (glm::abs(angle_v) <= glm::epsilon<float>() || glm::abs(angle_v - 180.0f) <= glm::epsilon<float>())return camera_matrix;


		glm::vec3 direction(glm::sin(glm::radians(angle_v)) * glm::sin(glm::radians(angle_h)),
			glm::cos(glm::radians(angle_v)),
			glm::sin(glm::radians(angle_v)) * glm::cos(glm::radians(angle_h)));

		camera_pos = camera_origin + radius * direction;

		if (angle_v > 0.0f && angle_v < 180.0f)
		{
			camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
		}
		else
		{
			camera_up = glm::vec3(0.0f, -1.0f, 0.0f);
		}

		camera_matrix = glm::perspective(FOV, viewport_size.x / (float)viewport_size.y, 0.1f, 1000.0f);
		camera_matrix *= glm::lookAt(camera_pos, camera_origin, camera_up);

		return camera_matrix;
	}
	// difference = scale * (newpos - currpos) / [width, height - panelu]
	//-difference.y * direction + -difference.x * prostopadly;
	void Camera::setTarget(glm::vec3 position)
	{
		camera_origin = position;
	}

	void Camera::setTarget(float x, float y, float z)
	{
		camera_origin = glm::vec3(x, y, z);
	}

	void Camera::setViewportSize(glm::vec2 viewport)
	{
		viewport_size = viewport;
	}

	void Camera::rotateVertical(float angle)
	{
		angle_v += angle;
	}

	void Camera::rotateHorizontal(float angle)
	{
		angle_h += angle;
	}

	void Camera::moveTarget(glm::vec3 vecXYZ)
	{
		camera_origin += vecXYZ;
	}

	void Camera::moveTarget(float X, float Y, float Z)
	{
		camera_origin += glm::vec3(X, Y, Z);
	}

	void Camera::moveCamera(glm::vec2 XY)
	{
		glm::vec3 direction = glm::normalize(
			glm::vec3(glm::sin(glm::radians(angle_v)) * glm::sin(glm::radians(angle_h)),
			0.0f,
			glm::sin(glm::radians(angle_v)) * glm::cos(glm::radians(angle_h)))
			);

		glm::vec3 tangent = glm::normalize(
			glm::vec3(glm::sin(glm::radians(angle_v)) * glm::sin(glm::radians(angle_h + 90.0f)),
				0.0f,
				glm::sin(glm::radians(angle_v)) * glm::cos(glm::radians(angle_h + 90.0f)))
		);

		moveTarget(-XY.y * direction - XY.x*tangent);

	}

	void Camera::moveCamera(float X, float Y)
	{
		moveCamera(glm::vec2(X, Y));
	}

	void Camera::setDistance(float distance)
	{
		radius = distance;
	}

	glm::vec3 Camera::getTarget()const
	{
		return camera_origin;
	}

}