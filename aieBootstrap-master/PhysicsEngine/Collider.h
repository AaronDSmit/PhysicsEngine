#ifndef Collider_H
#define Collider_H

#include <glm/glm.hpp>

enum ColliderType
{
	PLANE = 0,
	CIRLCE,
	AABB,
	SHAPE_COUNT = 3,
	POLYGON
};

/// <summary>
/// The Collider class serves as every type of collider. The ColliderType enum is used during broad phase to terminate the collision check chain when it's no longer necessary
/// to use further checking.
/// </summary> 

class Collider
{
public:
	Collider() = default;

	// Circle Constructor
	Collider(ColliderType type, class Shape* shape, float radius);

	// AABB Constructor
	Collider(ColliderType type, class Shape* shape, glm::vec2 extents);

	// Plane Constructor
	Collider(ColliderType type, class Shape* shape, glm::vec2 normal, float distanceToOrigin);

	// Polygon Constructor
	Collider(ColliderType type, class Shape* shape, glm::vec2* verts);

	void OnCollisionEnter(Collider* other);
	void OnCollisionExit(Collider* other);

	glm::vec2 getPosition() const;

	// Circle Collider
	void setRadius(float radius) { m_radius = radius; }
	float getRadius() const { return m_radius; }

	// Plane Collider
	glm::vec2 getNormal() const { return m_normal; }
	float getDistanceToOrigin() const { return m_distanceToOrigin; }

	// AABB Collider
	glm::vec2 getBL() const;
	glm::vec2 getTL() const;
	glm::vec2 getTR() const;
	glm::vec2 getBR() const;

	void setExtents(glm::vec2 extents) { m_extents = extents; }
	glm::vec2 getExtents() const { return m_extents; }

	ColliderType getType() const { return m_type; }

	~Collider() = default;

protected:

	ColliderType m_type;
	class Shape* m_shape;

	// Circle Info
	float m_radius;

	// Plane Info
	glm::vec2 m_normal;
	float m_distanceToOrigin;

	// AABB Info
	glm::vec2 m_extents;
};

#endif // !Collider_H