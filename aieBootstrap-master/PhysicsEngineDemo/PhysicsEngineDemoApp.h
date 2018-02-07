#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <glm/glm.hpp>


class PhysicsEngineDemoApp : public aie::Application
{
public:

	PhysicsEngineDemoApp();
	virtual ~PhysicsEngineDemoApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	class SceneManager* m_manager;
	glm::vec4 backgroundColour;
	class MenuScene* m_menu;
};