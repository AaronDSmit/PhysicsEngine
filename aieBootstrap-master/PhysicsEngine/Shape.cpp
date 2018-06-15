#include "Shape.h"
#include "Renderer2D.h"
#include "RigidBody.h"
#include "Joint.h"
#include <memory>

Shape::Shape(glm::vec2 position, glm::vec2* vertices, unsigned int numOfVertices, glm::vec4 colour)
	: PhysicsObject()
	, m_position(position)
	, m_vertices(vertices)
	, m_vertsCount(numOfVertices)
	, m_colour(colour)
{

}

void Shape::fixedUpdate(glm::vec2 gravity, float deltaTime)
{
	m_rigidBody->FixedUpdate(gravity, deltaTime);

	if (m_joint)
	{
		m_joint->FixedUpdate(gravity, deltaTime);
	}
}

void Shape::draw(aie::Renderer2D* renderer)
{
	renderer->setRenderColour(m_colour.x, m_colour.y, m_colour.z, 1);

	for (unsigned int i = 0; i < m_vertsCount - 1; i++)
	{
		renderer->drawLine(m_position.x + m_vertices[i].x, m_position.y + m_vertices[i].y, m_position.x + m_vertices[i + 1].x, m_position.y + m_vertices[i + 1].y);
	}

	renderer->drawLine(m_position.x + m_vertices[m_vertsCount - 1].x, m_position.y + m_vertices[m_vertsCount - 1].y, m_position.x + m_vertices[0].x, m_position.y + m_vertices[0].y);

	// Draw centre point
	renderer->drawCircle(m_position.x, m_position.y, 1.0f);

	// Draw joints
	/*for (int i = 0; i < m_joints.size(); i++)
	{

	}*/

	if (m_joint)
	{
		m_joint->draw(renderer);
	}
}
