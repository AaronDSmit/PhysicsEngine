#include "PhysicsEngineApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "PhysicsScene.h"

PhysicsEngineApp::PhysicsEngineApp()
{

}

PhysicsEngineApp::~PhysicsEngineApp()
{

}

bool PhysicsEngineApp::startup()
{
	m_2dRenderer = new aie::Renderer2D();
	m_scene = std::make_unique<PhysicsScene>();

	setVSync(true);

	return true;
}

void PhysicsEngineApp::shutdown()
{
	delete m_2dRenderer;
}

void PhysicsEngineApp::update(float deltaTime)
{
	m_scene->Update(deltaTime);

	// exit the application
	if (aie::Input::getInstance()->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsEngineApp::draw()
{
	clearScreen();

	m_2dRenderer->begin();

	// get the background colour of the scene and set the renderer's clear screen colour to it.
	m_backgroundColour = m_scene->getBackgroundColour();
	setBackgroundColour(m_backgroundColour.x, m_backgroundColour.y, m_backgroundColour.z, m_backgroundColour.w);

	m_scene->Draw(m_2dRenderer);

	m_2dRenderer->end();
}