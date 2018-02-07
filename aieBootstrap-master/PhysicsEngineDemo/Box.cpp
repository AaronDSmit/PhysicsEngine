#include "Box.h"
#include <Gizmos.h>

Box::Box(glm::vec2 position, glm::vec2 velocity, float mass, float length, float height, glm::vec4 colour) : RigidBody(BOX, position, velocity, 0, mass)
{
	m_position = position;
	m_velocity = velocity;
	m_mass = mass;
	m_colour = colour;
	m_length = length;
	m_height = height;
}

void Box::MakeGizmo()
{
	aie::Gizmos::add2DAABBFilled(m_position, glm::vec2(m_length, m_height), m_colour);
}

void Box::Debug()
{

}

Box::~Box()
{

}