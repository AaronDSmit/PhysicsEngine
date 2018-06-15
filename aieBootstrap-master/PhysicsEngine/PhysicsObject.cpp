#include "PhysicsObject.h"
#include "Collider.h"
#include "RigidBody.h"

PhysicsObject::PhysicsObject()
{

}

void PhysicsObject::addRigidBody(std::unique_ptr<RigidBody> rigidBody)
{
	m_rigidBody = std::move(rigidBody);
}

void PhysicsObject::removeRigidBody()
{
	m_rigidBody.reset();
}

void PhysicsObject::addCollider(std::unique_ptr<Collider> collider)
{
	m_collider = std::move(collider);
}

void PhysicsObject::removeCollider()
{
	m_collider.reset();
}

void PhysicsObject::addSpring(std::unique_ptr<Spring> spring)
{
	m_joint = std::move(spring);
	// m_joints.push_back(std::move(spring));
}

PhysicsObject::~PhysicsObject()
{

}