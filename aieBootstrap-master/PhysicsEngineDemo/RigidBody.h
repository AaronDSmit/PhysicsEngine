#ifndef RigidBody_H
#define RigidBody_H

#include <glm/glm.hpp>

#include "PhysicsObject.h"

enum ForceMode
{
	FORCE,
	ACCELERATION,
	IMPULSE,
	VELOCITYCHANGE
};

class RigidBody :public PhysicsObject
{
public:
	RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass);

	virtual void FixedUpdate(glm::vec2 gravity, float fixedDeltaTime) override;

	virtual void Debug() override;

	virtual void MakeGizmo() override;

	void ApplyForce(glm::vec2 force, ForceMode forceMode);

	virtual void OnCollisionEnter(PhysicsObject* other);
	virtual void OnCollision(PhysicsObject* other);
	virtual void OnCollisionExit(PhysicsObject* other);

	// Getters
	glm::vec2 GetPosition() { return m_position; }
	glm::vec2 GetVelocity() { return m_velocity; }
	float GetRotation() { return m_rotation; }
	float GetMass() { return m_mass; }

	RigidBody() = delete;

	~RigidBody();

protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_mass;
	float m_rotation;
};

#endif // !RigidBody_H