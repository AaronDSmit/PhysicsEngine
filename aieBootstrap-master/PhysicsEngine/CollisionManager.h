#ifndef CollisionManager_H
#define CollisionManager_H

#include <vector>
#include <glm/glm.hpp>
#include <memory>
#include "QuadTree.h"

namespace aie
{
	class Renderer2D;
}

/// <summary>
/// Used solely by the Collision Manager, this class holds all the information regarding a collision and is used when separating and resolving them.
/// </summary> 

struct Collision
{
	Collision() { depth = 0.0f, normal = { 0.0f, 0.0f }, collision = false; };
	Collision(float _depth, glm::vec2 _normal, bool _collision) { depth = _depth; normal = _normal; collision = _collision; };
	Collision(bool _collision) { depth = 0.0f, normal = { 0.0f, 0.0f }, collision = _collision; };

	float depth;
	glm::vec2 normal;
	bool collision;
};

/// <summary>
/// The collision Manager class is used by the physics scene to check for collisions between all Dynamic PhysicsObjects. 
/// It uses a quad tree class to partition the screen space into 4 equal boxes. Each Physics Object is only checked against objects in the same node and it's parent.
/// Collision checks are done with three phrases, First objects are compared by their bounding boxes, then by their bounding circle if not AABB vs AABB.
/// and then using a lookup table. SAT would be the next step if a polygon shape is involved in the check and all previous checks tested positive.
/// </summary> 

class CollisionManager
{
public:

	CollisionManager() = delete;

	CollisionManager(class PhysicsScene* scene);

	void checkCollisions(std::vector<class PhysicsObject*>& m_actors);

	void draw(class aie::Renderer2D* renderer);

	static Collision planeToCircle(class PhysicsObject* obj1, class PhysicsObject* obj2);
	static Collision planeToAABB(class PhysicsObject* obj1, class PhysicsObject* obj2);
	static Collision circleToPlane(class PhysicsObject* obj1, class PhysicsObject* obj2);
	static Collision circleToAABB(class PhysicsObject* obj1, class PhysicsObject* obj2);
	static Collision circleToCircle(class PhysicsObject* obj1, class PhysicsObject* obj2);
	static Collision AABBToPlane(class PhysicsObject* obj1, class PhysicsObject* obj2);
	static Collision AABBToCircle(class PhysicsObject* obj1, class PhysicsObject* obj2);
	static Collision AABBToAABB(class PhysicsObject* obj1, class PhysicsObject* obj2);

	~CollisionManager() = default;

private:
	void seperateCollision(const Collision _collision, class PhysicsObject* obj1, class PhysicsObject* obj2);
	void resolveCollision(const Collision _collision, class PhysicsObject* obj1, class PhysicsObject* obj2);

	bool checkAABBCollisions(class PhysicsObject* obj1, class PhysicsObject* obj2) const;
	bool checkCircleCollisions(class PhysicsObject* obj1, class PhysicsObject* obj2) const;

	std::unique_ptr<class QuadTree> m_tree;

	bool m_useQuadTree;
	bool m_shatter;

	class PhysicsScene* m_scene;

	std::vector<class PhysicsObject*> m_objectList;
};

#endif // !CollisionManager