#include "Joint.h"
#include "RigidBody.h"
#include "Renderer2D.h"

Joint::Joint()
{

}

Joint::Joint(RigidBody* body1, RigidBody* body2)
	: m_body1(body1)
	, m_body2(body2)
{

}

void Joint::draw(aie::Renderer2D* renderer)
{
	renderer->setRenderColour(1.0f, 1.0f, 1.0f);

	renderer->drawLine(m_body1->getPosition().x, m_body1->getPosition().y, m_body2->getPosition().x, m_body2->getPosition().y);
}