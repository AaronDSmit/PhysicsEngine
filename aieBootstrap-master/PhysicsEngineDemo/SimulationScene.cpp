#include "SimulationScene.h"
#include "Font.h"
#include "PhysicsObject.h"
#include <iostream>

#include "Box.h"

void SimulationScene::HandleInput()
{
	if (m_input->wasKeyPressed(aie::INPUT_KEY_ESCAPE))
	{
		m_manager->PopScene();
	}
}

SimulationScene::SimulationScene(SceneManager * manager) : Scene(manager)
{
	m_manager = manager;

	m_font = new aie::Font("./font/consolas.ttf", 32);

	backgroundColour = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

	m_input = aie::Input::getInstance();

	Box* box = new Box(glm::vec2(), glm::vec2(), 5, 20, 10, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	m_actors.push_back(box);

	m_timeStep = 0.01f;
}

void SimulationScene::Update(float deltaTime)
{
	FixedUpdate(deltaTime);
	HandleInput();
}

void SimulationScene::FixedUpdate(float deltaTime)
{
	static float accumulatedTime = 0.0f;
	accumulatedTime += deltaTime;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto actor : m_actors)
		{
			actor->FixedUpdate(m_gravity, deltaTime);
		}

		accumulatedTime -= m_timeStep;

		//collisionChecker.CheckCollisions(m_actors);
	}
}

void SimulationScene::Draw()
{
	for (auto actor : m_actors)
	{
		actor->MakeGizmo();
	}
}

SimulationScene::~SimulationScene()
{
	for (auto actor : m_actors)
	{
		delete actor;
	}
}