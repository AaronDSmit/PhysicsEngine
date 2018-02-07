#ifndef SimulationScene_H
#define SimulationScene_H

#include "Scene.h"

class SimulationScene : public Scene
{
protected:
	// handles input while scene is active
	void HandleInput() override;

public:
	SimulationScene(SceneManager* manager);

	SimulationScene() = delete;

	// Update function called every frame
	void Update(float deltaTime) override;

	// Physics Update
	virtual void FixedUpdate(float deltaTime) override;

	// Draw to screen called every frame
	void Draw() override;

	// default deconstructor
	~SimulationScene();

protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<class PhysicsObject*> m_actors;
	aie::Font* m_font;
};

#endif // !SimulationScene_H