#include "RigidBody.h"
#include "Shape.h"


void RigidBody::Translate(glm::vec2 translation)
{
	m_position += translation;

	m_shape->setPosition(m_position);
}

RigidBody::~RigidBody()
{
}

RigidBody::RigidBody(Shape* shape, glm::vec2 velocity, float mass)
	: m_shape(shape)
	, m_position(shape->getPosition())
	, m_velocity(velocity)
	, m_acceleration({ 0.0f,0.0f })
	, m_mass(mass)
	, m_iskinematic(false)
{

}

void RigidBody::FixedUpdate(glm::vec2 gravity, float fixedDeltaTime)
{
	if (m_iskinematic)
		return;

	ApplyForce(gravity, ACCELERATION);

	m_velocity += m_acceleration * fixedDeltaTime;

	Translate(m_velocity * fixedDeltaTime);

	m_acceleration = { 0,0 };
}

void RigidBody::ApplyForce(glm::vec2 force, ForceMode forceMode)
{
	if (glm::length(force) == 0)
	{
		return;
	}

	switch (forceMode)
	{
	case ForceMode::FORCE:
		m_acceleration += force / m_mass;
		break;
	case ForceMode::ACCELERATION:
		m_acceleration += force;
		break;
	case ForceMode::IMPULSE:
		m_velocity += force / m_mass;
		break;
	case ForceMode::VELOCITYCHANGE:
		m_velocity += force;
		break;
	}
}

void RigidBody::setPosition(glm::vec2 position)
{
	m_position = position;
	m_shape->setPosition(m_position);
}
