#include "RigidBody.h"

#include <iostream>

RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass) : PhysicsObject(shapeID)
{
	m_shapeID = shapeID;
	m_position = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_mass = mass;
}

void RigidBody::FixedUpdate(glm::vec2 gravity, float fixedDeltaTime)
{
	ApplyForce(gravity * m_mass, ACCELERATION);

	m_position += m_velocity * fixedDeltaTime;
}

void RigidBody::Debug()
{

}

void RigidBody::MakeGizmo()
{

}

void RigidBody::ApplyForce(glm::vec2 force, ForceMode forceMode)
{
	m_velocity += (force / m_mass);
}

void RigidBody::OnCollisionEnter(PhysicsObject * other)
{
	std::cout << "Collision Enter" << std::endl;
}

void RigidBody::OnCollision(PhysicsObject * other)
{
	std::cout << "Collision happening" << std::endl;
}

void RigidBody::OnCollisionExit(PhysicsObject * other)
{
	std::cout << "Collision exit" << std::endl;
}

RigidBody::~RigidBody()
{

}