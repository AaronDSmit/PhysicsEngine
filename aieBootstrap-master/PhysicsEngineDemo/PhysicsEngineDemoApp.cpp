#include "PhysicsEngineDemoApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "SceneManager.h"
#include "Scene.h"
#include "MenuScene.h"


PhysicsEngineDemoApp::PhysicsEngineDemoApp()
{

}

PhysicsEngineDemoApp::~PhysicsEngineDemoApp()
{

}

bool PhysicsEngineDemoApp::startup()
{
	m_2dRenderer = new aie::Renderer2D();
	m_manager = new SceneManager();

	m_menu = new MenuScene(m_manager);

	m_manager->PushScene(m_menu);

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	return true;
}

void PhysicsEngineDemoApp::shutdown()
{
	delete m_font;
	delete m_2dRenderer;
	delete m_manager;
}

void PhysicsEngineDemoApp::update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	if (m_manager != nullptr)
	{
		m_manager->Update(deltaTime);
	}

	// exit the application
	if (input->wasKeyPressed(aie::INPUT_KEY_ESCAPE))
	{
		if (m_manager->PeekScene() == m_menu)
		{
			//quit();
		}
	}
}

void PhysicsEngineDemoApp::draw()
{
	if (m_manager != nullptr)
	{
		backgroundColour = m_manager->PeekScene()->getBackgroundColour();

		setBackgroundColour(backgroundColour.x, backgroundColour.y, backgroundColour.z, backgroundColour.w);

		m_manager->Draw();
	}

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!


	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "" + getFPS(), 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}