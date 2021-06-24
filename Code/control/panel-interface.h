#pragma once

#include "control-interface.h"
#include "panel-blueprint.h"
#include "../render/observer.h"
#include "../render/scene.h"

namespace vrt::gui
{
	class PanelInterface : public ControlInterface, public utils::Observer
	{
	public:
		PanelInterface(PanelBlueprint blueprint, short ID, ControlInterface* parent);
		virtual ~PanelInterface();

		virtual void show(int cmd_show) = 0;
		void update(const std::string& message_from_subject);

		void setScene(render::Scene* scene);
	protected:
		render::Scene* scene;

		//void handleEvent(const event::Event& event) final;

	private:
	};
}