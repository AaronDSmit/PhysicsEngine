#ifndef RigidBody_H
#define RigidBody_H

#include "PhysicsObject.h"

class RigidBody :public PhysicsObject
{
public:
	RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass);

	virtual void FixedUpdate(glm::vec2 gravity, float fixedDeltaTime) override;

	virtual void Debug() override;

	virtual void MakeGizmo() override;

	RigidBody() = delete;

	~RigidBody();
};

#endif // !RigidBody_H