#pragma once

#include "control-interface.h"
#include "panel-blueprint.h"
#include "../render/observer.h"
#include "../render/scene.h"
#include "../render/camera.h"

namespace vrt::gui
{
	class PanelInterface : public ControlInterface, public utils::Observer
	{
	public:
		PanelInterface(PanelBlueprint blueprint, short ID, ControlInterface* parent);
		virtual ~PanelInterface();

		virtual void show(int cmd_show) = 0;
		void setScene(render::Scene* scene);
		virtual void render();

		render::Camera & getCamera();

	protected:
		render::Scene* scene;
		render::Camera camera;

		void handleEvent(const event::Event& event) final;
		void update(const std::string& message_from_subject) override;

	private:

	};
}