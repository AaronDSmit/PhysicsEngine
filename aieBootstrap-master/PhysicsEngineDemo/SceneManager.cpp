#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager()
{
	endGame = false;
}

void SceneManager::Update(float deltaTime)
{
	PeekScene()->Update(deltaTime);
}

void SceneManager::Draw()
{
	PeekScene()->Draw();
}

void SceneManager::PushScene(Scene* a_scene)
{
	scenes.push(a_scene);
}

void SceneManager::PopScene()
{
	scenes.pop();
}

void SceneManager::PopBackToFirst()
{
	while (scenes.size() > 1)
	{
		scenes.pop();
	}
}

void SceneManager::ChangeScene(Scene* a_scene)
{
	if (!scenes.empty())
	{
		PopScene();
	}

	PushScene(a_scene);
}

Scene * SceneManager::PeekScene()
{
	if (scenes.empty())
	{
		return nullptr;
	}

	return scenes.top();
}

void SceneManager::EndGame()
{
	endGame = true;
}

SceneManager::~SceneManager()
{
	while (!scenes.empty()) {
		PopScene();
	}
}