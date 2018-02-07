#include "MenuScene.h"
#include <glm/glm.hpp>
#include "Font.h"
#include "SimulationScene.h"

MenuScene::MenuScene(SceneManager* manager) : Scene(manager)
{
	m_manager = manager;

	font = new aie::Font("./font/consolas.ttf", 32);

	backgroundColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	m_input = aie::Input::getInstance();
}

void MenuScene::Update(float deltaTime)
{
	HandleInput();
}

void MenuScene::FixedUpdate(float deltaTime)
{

}

void MenuScene::Draw()
{

}

MenuScene::~MenuScene()
{
	delete &m_input;
}

void MenuScene::HandleInput()
{
	if (m_input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		m_manager->PushScene(new SimulationScene(m_manager));
	}

	if (m_input->wasKeyPressed(aie::INPUT_KEY_ESCAPE))
	{
		m_manager->EndGame();
	}
}