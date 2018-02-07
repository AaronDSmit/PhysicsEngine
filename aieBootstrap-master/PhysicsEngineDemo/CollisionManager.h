#ifndef CollisionController_H
#define CollisionController_H

#include <vector>

class PhysicsObject;

class CollisionManager
{
public:
	CollisionManager();

	void CheckCollisions(std::vector<PhysicsObject*>& m_actors);

	void ResolveCollisions();

	std::vector<class Collision*> collisionList;

	static bool PlaneToPlane(PhysicsObject*, PhysicsObject*);
	static bool PlaneToSphere(PhysicsObject*, PhysicsObject*);
	static bool PlaneToBox(PhysicsObject*, PhysicsObject*);
	static bool SphereToPlane(PhysicsObject*, PhysicsObject*);
	static bool SphereToBox(PhysicsObject*, PhysicsObject*);
	static bool SphereToSphere(PhysicsObject*, PhysicsObject*);
	static bool BoxToPlane(PhysicsObject*, PhysicsObject*);
	static bool BoxToSphere(PhysicsObject*, PhysicsObject*);
	static bool BoxToBox(PhysicsObject*, PhysicsObject*);

	~CollisionManager();
};

#endif // !CollisionController
