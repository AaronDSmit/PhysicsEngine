#include "RigidBody.h"


RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass) : PhysicsObject(shapeID)
{

}

void RigidBody::FixedUpdate(glm::vec2 gravity, float fixedDeltaTime)
{

}

void RigidBody::Debug()
{

}

void RigidBody::MakeGizmo()
{

}

RigidBody::~RigidBody()
{

}