#ifndef SceneManager_H
#define SceneManager_H

#include <stack>

class SceneManager
{
public:
	SceneManager();

	// Loops through all game objects and calls their update function
	void Update(float deltaTime);

	// Loops through all game objects and draws them
	void Draw();

	// State Management
	void PushScene(class Scene* a_scene);
	void PopScene();
	void PopBackToFirst();
	void ChangeScene(class Scene* a_scene);
	class Scene* PeekScene();

	void EndGame();

	~SceneManager();

private:

	bool endGame;
	std::stack<Scene*> scenes;
};

#endif // !SceneManager_H