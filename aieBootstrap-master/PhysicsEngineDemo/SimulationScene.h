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

	void SetGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	glm::vec2 getGravity() const { return m_gravity; }

	// Draw to screen called every frame
	void Draw() override;

	// default deconstructor
	~SimulationScene();

protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	aie::Font* m_font;
};

#endif // !SimulationScene_H