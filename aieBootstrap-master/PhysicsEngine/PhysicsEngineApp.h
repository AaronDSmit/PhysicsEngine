#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <glm/glm.hpp>
#include <memory>

class PhysicsEngineApp : public aie::Application
{
public:

	PhysicsEngineApp();
	virtual ~PhysicsEngineApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	std::unique_ptr<class PhysicsScene> m_scene;
	glm::vec4 m_backgroundColour;
};