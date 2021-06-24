#include "control-interface.h"
#include "../log/log.h"

namespace vrt::gui
{
	ControlInterface::ControlInterface(unsigned int ID_arg, const ControlBlueprint& blueprint, ControlInterface * parent)
	{
		initialized = false;

		setPosition(blueprint.position);
		setSize(blueprint.size);
		setControlName(blueprint.name);
		setID(ID_arg);
		setParent(parent);

		LOG_INF("ControlInterface() id: " << ID_arg);
	}

	ControlInterface::ControlInterface(const ControlInterface& other)
	{
		// TODO
	}

	ControlInterface::~ControlInterface()
	{
		LOG_INF("~ControlInterface()");
		// TODO
	}

	void ControlInterface::handleEvent(const event::Event& event)
	{
		LOG_WAR("Default handleEvent for "<<getControlName());
	}

	ControlInterface& ControlInterface::operator=(const ControlInterface& other)
	{
		// TODO: tu wstawiæ instrukcjê return
		return *this;
	}

	ControlInterface::operator bool() const noexcept
	{
		return initialized;
	}

	void ControlInterface::setPosition(glm::ivec2 position)
	{
		position = std::move(position);
	}

	void ControlInterface::setPosition(int x, int y)
	{
		position.x = x;
		position.y = y;
	}

	void ControlInterface::setSize(glm::ivec2 size)
	{
		size = std::move(size);
	}

	void ControlInterface::setSize(int width, int height)
	{
		size.x = width;
		size.y = height;
	}

	void ControlInterface::setControlName(std::string name_arg)
	{
		control_name = std::move(name_arg);
	}

	void ControlInterface::setParent(ControlInterface* parent_arg)
	{
		parent = parent_arg;
	}

	glm::ivec2 ControlInterface::getPosition() const
	{
		return position;
	}

	glm::ivec2 ControlInterface::getSize() const
	{
		return size;
	}

	const std::string & ControlInterface::getControlName() const
	{
		return control_name;
	}

	ControlInterface* ControlInterface::getParent() const
	{
		return parent;
	}

	unsigned int ControlInterface::getID()
	{
		return ID;
	}

	void ControlInterface::setID(unsigned int id)
	{
		ID = id;
	}

	void ControlInterface::setAsInitialized()
	{
		initialized = true;
	}
}