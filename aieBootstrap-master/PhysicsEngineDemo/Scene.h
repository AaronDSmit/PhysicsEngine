#ifndef Scene_H
#define Scene_H

#include <glm/glm.hpp>
#include "Renderer2D.h"
#include "Input.h"
#include "SceneManager.h"

class Scene
{
protected:
	// handles input while scene is active
	virtual void HandleInput() = 0;

public:
	Scene(SceneManager* manager);
	Scene() = delete;

	// Update function called every frame
	virtual void Update(float deltaTime) = 0;

	// Physics Update
	virtual void FixedUpdate(float deltaTime) = 0;

	// Draw to screen called every frame
	virtual void Draw() = 0;

	glm::vec4 getBackgroundColour() { return backgroundColour; }

protected:
	aie::Input* m_input;
	SceneManager* m_manager;
	std::vector<class PhysicsObject*> m_actors;
	glm::vec4 backgroundColour;

	~Scene();
};

#endif // !Scene_H