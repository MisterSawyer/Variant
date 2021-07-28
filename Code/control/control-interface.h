#pragma once

#include "../events/events.h"
#include "../Code/control/control-blueprint.h"

#include <string>
#include <list>
#include <GLM/glm.hpp>
#include <memory>

namespace vrt::gui
{
	/*
	* The abstract control class from which all others inherit
	*/
	class ControlInterface
	{
	public:
		ControlInterface(unsigned int ID, const ControlBlueprint& blueprint, ControlInterface * parent);
		explicit ControlInterface(const ControlInterface& other) = delete; // done by factory and blueprints
		virtual	~ControlInterface();
		ControlInterface& operator=(const ControlInterface& other) = delete;

		explicit operator bool() const noexcept;

		void						setPosition(glm::ivec2 position);
		void						setPosition(int x, int y);
		void						setSize(glm::ivec2 size);
		void						setSize(int width, int height);
		void						setControlName(std::string name);
		void						setParent(ControlInterface* parent);
		void						addChild(ControlInterface * child);
		void						deleteChild(ControlInterface * child);

		glm::ivec2 					getPosition() const;
		glm::ivec2					getSize() const;
		const std::string &			getControlName()const;
		ControlInterface*			getParent() const;
		unsigned int				getID() const;
	protected:
		void setID(unsigned int id);
		void setAsInitialized();
		virtual void propagateEvent(const event::Event& event);
		//virtual void postEvent(const event::Event& event) = 0;
		virtual void handleEvent(const event::Event& event);

	private:
		unsigned int ID;
		bool initialized;
		ControlInterface* parent;
		std::list<ControlInterface*> children;
		glm::ivec2 position;
		glm::ivec2 size;
		std::string control_name;
	};
}