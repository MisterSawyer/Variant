#include "transformable.h"
#include "../Code/log/log.h"

namespace vrt {

	Transformable::Transformable()
	{
		position_ = glm::vec3(0.0f, 0.0f, 0.0f);
		rotation_ = glm::vec3(0.0f, 0.0f, 0.0f);
		scale_ = glm::vec3(1.0f, 1.0f, 1.0f);
		to_update_ = true;
	}

	Transformable::Transformable(glm::vec3 position)
	{
		position_ = position;
		rotation_ = glm::vec3(0.0f, 0.0f, 0.0f);
		scale_ = glm::vec3(1.0f, 1.0f, 1.0f);
		matrix_ = glm::mat4();
		to_update_ = true;
	}

	Transformable::Transformable(float pos_x, float pos_y, float pos_z)
	{
		position_ = glm::vec3(pos_x, pos_y, pos_z);
		rotation_ = glm::vec3(0.0f, 0.0f, 0.0f);
		scale_ = glm::vec3(1.0f, 1.0f, 1.0f);
		matrix_ = glm::mat4();
		to_update_ = true;
	}

	Transformable::Transformable(const Transformable& other)
	{
		position_ = other.position_;
		rotation_ = other.rotation_;
		scale_ = other.scale_;
		matrix_ = glm::mat4();
		to_update_ = true;
	}

	Transformable::Transformable(Transformable&& other)noexcept
	{
		position_ = std::move(other.position_);
		rotation_ = std::move(other.rotation_);
		scale_ = std::move(other.scale_);
		matrix_ = glm::mat4();
		to_update_ = true;
	}

	Transformable& Transformable::operator=(const Transformable& other)
	{
		if (this == &other)
		{
			LOG_WAR("Self assigment");
			return *this;
		}

		position_ = other.position_;
		rotation_ = other.rotation_;
		scale_ = other.scale_;
		to_update_ = true;

		return *this;
	}

	Transformable& Transformable::operator=(Transformable&& other)noexcept
	{
		if (this == &other)
		{
			LOG_WAR("Self move assigment");
			return *this;
		}
		position_ = std::move(other.position_);
		rotation_ = std::move(other.rotation_);
		scale_ = std::move(other.scale_);
		to_update_ = true;

		return *this;
	}

	void Transformable::setPosition(glm::vec3 position)
	{
		this->position_ = position;
		to_update_ = true;
	}

	void Transformable::setPosition(float x, float y, float z)
	{
		this->position_.x = x;
		this->position_.y = y;
		this->position_.z = z;
		to_update_ = true;
	}

	void Transformable::setPositionX(float x)
	{
		this->position_.x = x;
		to_update_ = true;
	}

	void Transformable::setPositionY(float y)
	{
		this->position_.y = y;
		to_update_ = true;
	}

	void Transformable::setPositionZ(float z)
	{
		this->position_.z = z;
		to_update_ = true;
	}

	void Transformable::setRotation(glm::vec3 rotation)
	{
		this->rotation_ = rotation;
		to_update_ = true;
	}

	void Transformable::setRotation(float x, float y, float z)
	{
		this->rotation_.x = x;
		this->rotation_.y = y;
		this->rotation_.z = z;
		to_update_ = true;
	}

	void Transformable::setRotationX(float x)
	{
		this->rotation_.x = x;
		to_update_ = true;
	}

	void Transformable::setRotationY(float y)
	{
		this->rotation_.y = y;
		to_update_ = true;
	}

	void Transformable::setRotationZ(float z)
	{
		this->rotation_.z = z;
		to_update_ = true;
	}

	void Transformable::setScale(glm::vec3 scale)
	{
		this->scale_ = scale;
		to_update_ = true;
	}

	void Transformable::setScale(float x, float y, float z)
	{
		this->scale_.x = x;
		this->scale_.y = y;
		this->scale_.z = z;
		to_update_ = true;
	}

	void Transformable::setScaleX(float x)
	{
		this->scale_.x = x;
		to_update_ = true;
	}

	void Transformable::setScaleY(float y)
	{
		this->scale_.y = y;
		to_update_ = true;
	}

	void Transformable::setScaleZ(float z)
	{
		this->scale_.z = z;
		to_update_ = true;
	}

	glm::vec3 Transformable::getPosition() const
	{
		return this->position_;
	}

	glm::vec3 Transformable::getRotation() const
	{
		return this->rotation_;
	}

	glm::vec3 Transformable::getScale() const
	{
		return this->scale_;
	}

	float Transformable::getPositionX() const
	{
		return this->position_.x;
	}

	float Transformable::getPositionY() const
	{
		return this->position_.y;
	}

	float Transformable::getPositionZ() const
	{
		return this->position_.z;
	}

	float Transformable::getRotationX() const
	{
		return this->rotation_.x;
	}

	float Transformable::getRotationY() const
	{
		return this->rotation_.y;
	}

	float Transformable::getRotationZ() const
	{
		return this->rotation_.z;
	}

	float Transformable::getScaleX() const
	{
		return this->scale_.x;
	}

	float Transformable::getScaleY() const
	{
		return this->scale_.y;
	}

	float Transformable::getScaleZ() const
	{
		return this->scale_.z;
	}

	glm::mat4 Transformable::getMatrix()
	{
		update();
		return matrix_;
	}

	void Transformable::update()
	{
		if (!to_update_)return;
		matrix_ = glm::translate(glm::mat4(), position_);

		matrix_ = glm::rotate(matrix_, glm::radians(rotation_.x), glm::vec3(1.0, 0.0, 0.0));
		matrix_ = glm::rotate(matrix_, glm::radians(rotation_.y), glm::vec3(0.0, 1.0, 0.0));
		matrix_ = glm::rotate(matrix_, glm::radians(rotation_.z), glm::vec3(0.0, 0.0, 1.0));

		matrix_ = glm::scale(matrix_, scale_);
		to_update_ = false;
	}
}
