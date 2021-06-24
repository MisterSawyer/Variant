#include "view.h"

namespace vrt::gui
{
    View::View(const std::shared_ptr<AbstractGUIFactory>& factory)
    {
        gui_factory_ = factory;
    }

    WindowInterface * View::createWindow(const WindowBlueprint & blueprint, ControlInterface* parent, short ID)
    {
        short new_id = ID;
        while(taken_ids_.find(new_id) != taken_ids_.end())
        {
            ++new_id;
        }

        taken_ids_.insert(new_id);

        std::unique_ptr<WindowInterface> new_window = gui_factory_->createWindow(blueprint, new_id, parent);
        WindowInterface* return_value = new_window.get();

        auto ins = controls_.insert(std::make_pair(new_id, std::move(new_window)));
       
        if (ins.second) return return_value;

        return nullptr;
    }

    WindowInterface* View::createWindow(const WindowBlueprint & blueprint, short parent_id, short ID)
    {
        auto it = controls_.find(parent_id);

        if (it != controls_.end())return createWindow(blueprint, it->second.get(), ID);
        else return createWindow(blueprint,nullptr, ID);
    }

    ButtonInterface* View::createButton(const ButtonBlueprint & blueprint, ControlInterface* parent, short ID)
    {
        short new_id = ID;
        while (taken_ids_.find(new_id) != taken_ids_.end())
        {
            ++new_id;
        }

        taken_ids_.insert(new_id);

        std::unique_ptr<ButtonInterface> new_button = gui_factory_->createButton(blueprint, new_id, parent);
        ButtonInterface* return_value = new_button.get();

        auto ins = controls_.insert(std::make_pair(new_id, std::move(new_button)));

        if (ins.second) return return_value;

        return nullptr;
    }

    ButtonInterface* View::createButton(const ButtonBlueprint & blueprint, short parent_id, short ID)
    {
        auto it = controls_.find(parent_id);

        if (it != controls_.end())return createButton(blueprint, it->second.get(), ID);
        else return createButton(blueprint, nullptr, ID);
    }

    PanelInterface* View::createPanel(const PanelBlueprint& blueprint, ControlInterface* parent, short ID)
    {
        short new_id = ID;
        while (taken_ids_.find(new_id) != taken_ids_.end())
        {
            ++new_id;
        }

        taken_ids_.insert(new_id);

        std::unique_ptr<PanelInterface> new_button = gui_factory_->createPanel(blueprint, new_id, parent);
        PanelInterface* return_value = new_button.get();

        auto ins = controls_.insert(std::make_pair(new_id, std::move(new_button)));

        if (ins.second) return return_value;

        return nullptr;
    }

    PanelInterface* View::createPanel(const PanelBlueprint& blueprint, short parent_id, short ID)
    {
        auto it = controls_.find(parent_id);

        if (it != controls_.end())return createPanel(blueprint, it->second.get(), ID);
        else return createPanel(blueprint, nullptr, ID);
    }

}