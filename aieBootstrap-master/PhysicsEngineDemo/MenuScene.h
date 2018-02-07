#ifndef MenuScene_H
#define MenuScene_H

#include "Scene.h"

class MenuScene : public Scene
{
protected:
	// handles input while scene is active
	void HandleInput() override;
public:

	MenuScene(SceneManager* manager);

	// Default Constructor
	MenuScene() = delete;

	// Update function called every frame
	void Update(float deltaTime) override;

	// Physics Update
	virtual void FixedUpdate(float deltaTime) override;

	// Draw to screen called every frame
	void Draw() override;

	// default deconstructor
	~MenuScene();

private:
	aie::Font* font;
};

#endif // !MenuScene_H