#include "Collider.h"
#include "Shape.h"


Collider::Collider(ColliderType type, Shape* shape, float radius)
	: m_type(type)
	, m_shape(shape)
	, m_radius(radius)
	, m_normal(0.0f)
	, m_distanceToOrigin(0.0f)
	, m_extents({ radius * 2, radius * 2 })
{

}

Collider::Collider(ColliderType type, Shape * shape, glm::vec2 extents)
	: m_type(type)
	, m_shape(shape)
	, m_radius(0.0f)
	, m_normal(0.0f)
	, m_distanceToOrigin(0.0f)
	, m_extents(extents)
{

}

Collider::Collider(ColliderType type, Shape* shape, glm::vec2 normal, float distanceToOrigin)
	: m_type(type)
	, m_shape(shape)
	, m_radius(0.0f)
	, m_normal(normal)
	, m_distanceToOrigin(distanceToOrigin)
	, m_extents({ 0.0f, 0.0f })
{

}

Collider::Collider(ColliderType type, Shape * shape, glm::vec2 * verts)
{
}

void Collider::OnCollisionEnter(Collider * other)
{

}

void Collider::OnCollisionExit(Collider * other)
{

}

glm::vec2 Collider::getPosition() const
{
	return m_shape->getPosition();
}

glm::vec2 Collider::getBL() const
{
	return glm::vec2{ m_shape->getPosition().x - m_extents.x, m_shape->getPosition().y - m_extents.y };
}

glm::vec2 Collider::getTL() const
{
	return glm::vec2{ m_shape->getPosition().x - m_extents.x, m_shape->getPosition().y + m_extents.y };
}

glm::vec2 Collider::getTR() const
{
	return glm::vec2{ m_shape->getPosition().x + m_extents.x, m_shape->getPosition().y + m_extents.y };
}

glm::vec2 Collider::getBR() const
{
	return glm::vec2{ m_shape->getPosition().x + m_extents.x, m_shape->getPosition().y - m_extents.y };
}
