#include "Spring.h"
#include "RigidBody.h"
#include "Renderer2D.h"

Spring::Spring(RigidBody* body1, RigidBody* body2, float restLength, float springCoefficent, float damping)
	: Joint(body1, body2)
	, m_damping(damping)
	, m_restLength(restLength)
	, m_springCoefficent(springCoefficent)
{

}

void Spring::FixedUpdate(glm::vec2 gravity, float fixedDeltaTime)
{
	glm::vec2 dist = m_body2->getPosition() - m_body1->getPosition();
	float length = sqrtf(dist.x * dist.x + dist.y * dist.y);

	// Apply damping
	glm::vec2 relativeVel = m_body2->getVelocity() - m_body1->getVelocity();

	glm::vec2 force = { 0.0f, 0.0f };

	// F = -kx - bv
	if (glm::length(relativeVel) > 0.0f)
	{
		glm::vec2 firstHalf = dist * m_springCoefficent * (m_restLength - length);
		glm::vec2 secondHalf = m_damping * relativeVel;

		force = firstHalf - secondHalf;
	}

	m_body1->ApplyForce(-force * fixedDeltaTime, ForceMode::ACCELERATION);
	m_body2->ApplyForce(force * fixedDeltaTime, ForceMode::ACCELERATION);
}

void Spring::draw(aie::Renderer2D* renderer)
{
	renderer->setRenderColour(1.0f, 1.0f, 1.0f);

	renderer->drawLine(m_body1->getPosition().x, m_body1->getPosition().y, m_body2->getPosition().x, m_body2->getPosition().y);
}

Spring::~Spring()
{

}