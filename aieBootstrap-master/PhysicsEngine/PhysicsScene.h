#ifndef PhysicsScene_H
#define PhysicsScene_H

#include "CollisionManager.h"
#include "Input.h"
#include "Renderer2D.h"
#include <glm/glm.hpp>
#include <memory>

namespace aie
{
	class Renderer2D;
}

/// <summary>
/// The physics Scene is the class that owns the memory of every physics actor as well as a collision manager. It is responsible for calling every object's update and draw function
/// as well as providing the collision manager with an array of physics actors to check and resolve collisions.
/// </summary> 

class PhysicsScene
{
protected:

	// handles input while scene is active
	virtual void HandleInput();

	// Physics Update
	virtual void FixedUpdate(float deltaTime);

public:

	// Default Constructor
	PhysicsScene();

	// Copy Constructor
	PhysicsScene(const PhysicsScene&);

	// Update function called every frame
	virtual void Update(float deltaTime);

	void addActor(class PhysicsObject* actor);
	void RemoveActor(class PhysicsObject* actor);

	void setGravity(glm::vec2 gravity) { m_gravity = gravity; }
	glm::vec2 getGravity() const { return m_gravity; }

	void setTimeStep(float timeStep) { m_timeStep = timeStep; }
	float getTimeStep() const { return m_timeStep; }

	void setBackgroundColour(glm::vec4 colour) { m_backgroundColour = colour; }
	glm::vec4 getBackgroundColour() const { return m_backgroundColour; }

	// Functions to Create predefined Shapes
	void addCircle(glm::vec2 position, float radius, glm::vec4 colour, bool isKinematic = false, glm::vec2 velocity = { 0.0f, 0.0f }, float mass = 10.0f);

	void addPlane(glm::vec2 normal, float distanceToOrigin, glm::vec4 colour = { 1.0f, 1.0f, 1.0f, 1.0f });

	void addAABB(glm::vec2 position, glm::vec2 extents, glm::vec4 colour, bool isKinematic = false, glm::vec2 velocity = { 0.0f, 0.0f }, float mass = 10.0f);

	void addPolyon(glm::vec2 position, glm::vec2* verts, unsigned int vertCount, glm::vec4 colour, bool isKinematic = false, glm::vec2 velocity = { 0.0f, 0.0f }, float mass = 0.0f);

	void addSpring(class PhysicsObject* object1, class PhysicsObject* object2, float restLength, float springCoefficent, float damping = 0.1f);

	void ShatterObject(class PhysicsObject* object, glm::vec2 contactPoint);

	// Draw to screen called every frame
	virtual void Draw(aie::Renderer2D* renderer);

	~PhysicsScene();

protected:

	aie::Input* m_input;
	std::unique_ptr<CollisionManager> m_collisionManager;
	std::vector<class PhysicsObject*> m_actors;
	glm::vec4 m_backgroundColour;

	glm::vec2 m_gravity;
	float m_timeStep;
};

#endif // PhysicsScene_H