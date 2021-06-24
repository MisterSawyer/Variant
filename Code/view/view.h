#pragma once
#include "../control/abstract-gui-factory.h"
#include <unordered_map>
#include <set>

namespace vrt::gui
{
	class View
	{
	public:
		View(const std::shared_ptr<AbstractGUIFactory> & factory);
		/*
		template<class T, class Blueprint>
		T* create(const Blueprint& blueprint, ControlInterface* parent, short ID)
		{
			short new_id = ID;
			while (taken_ids_.find(new_id) != taken_ids_.end())
			{
				++new_id;
			}

			taken_ids_.insert(new_id);

			std::unique_ptr<T> new_object = gui_factory_->createButton(blueprint, new_id, parent);
			T * return_value = new_object.get();

			auto ins = controls_.insert(std::make_pair(new_id, std::move(new_object)));

			if (ins.second) return return_value;

			return nullptr;
		}
		*/
		WindowInterface * createWindow(const WindowBlueprint & blueprint, ControlInterface * parent = nullptr, short ID = 0);
		WindowInterface * createWindow(const WindowBlueprint & blueprint, short parent_id, short ID);

		ButtonInterface * createButton(const ButtonBlueprint & blueprint, ControlInterface * parent, short ID);
		ButtonInterface * createButton(const ButtonBlueprint & blueprint, short parent_id, short ID);

		PanelInterface * createPanel(const PanelBlueprint& blueprint, ControlInterface* parent, short ID);
		PanelInterface * createPanel(const PanelBlueprint& blueprint, short parent_id, short ID);

	private:
		std::set<short> taken_ids_;

		std::unordered_map<short, std::unique_ptr<ControlInterface>> controls_;

		std::shared_ptr<AbstractGUIFactory> gui_factory_;
	};
}