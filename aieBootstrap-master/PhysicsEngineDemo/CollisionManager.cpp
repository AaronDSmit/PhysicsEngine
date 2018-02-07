#include "CollisionManager.h"
#include "PhysicsObject.h"
#include "Collision.h"
#include <iostream>

typedef bool(*fn)(PhysicsObject*, PhysicsObject*);


static fn collisionFunctionArray[] =
{
	CollisionManager::PlaneToPlane, CollisionManager::PlaneToSphere,
	CollisionManager::PlaneToBox, CollisionManager::SphereToPlane,
	CollisionManager::SphereToSphere, CollisionManager::SphereToBox,
	CollisionManager::BoxToPlane, CollisionManager::BoxToSphere,
	CollisionManager::BoxToBox,
};

CollisionManager::CollisionManager()
{

}

void CollisionManager::CheckCollisions(std::vector<PhysicsObject*>& m_actors)
{
	int actorCount = m_actors.size();

	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount - 1; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
			int shapeID1 = object1->GetShapeID();
			int shapeID2 = object2->GetShapeID();

			int functionID = (shapeID1 * SHAPE_COUNT) + shapeID2;

			fn functionPtr = collisionFunctionArray[functionID];

			if (functionPtr != nullptr)
			{
				if (functionPtr(object1, object2))
				{
					collisionList.push_back(new Collision(object1, object2));
				}
			}
		}
	}
}

void CollisionManager::ResolveCollisions()
{
	for (auto collision : collisionList)
	{
		collision->obj1->OnCollision();
		collision->obj2->OnCollision();

		// Resovlve

		// check if still colliding

		// else remove them, and then delete it 
	}
}

CollisionManager::~CollisionManager()
{

}

bool CollisionManager::PlaneToPlane(PhysicsObject *, PhysicsObject *)
{
	std::cout << "PlaneToPlane" << std::endl;
	return false;
}

bool CollisionManager::PlaneToSphere(PhysicsObject *, PhysicsObject *)
{
	std::cout << "PlaneToSphere" << std::endl;
	return false;
}

bool CollisionManager::PlaneToBox(PhysicsObject *, PhysicsObject *)
{
	std::cout << "PlaneToBox" << std::endl;
	return false;
}

bool CollisionManager::SphereToPlane(PhysicsObject *, PhysicsObject *)
{
	std::cout << "SphereToPlane" << std::endl;
	return false;
}

bool CollisionManager::SphereToBox(PhysicsObject *, PhysicsObject *)
{
	std::cout << "SphereToBox" << std::endl;
	return false;
}

bool CollisionManager::SphereToSphere(PhysicsObject *, PhysicsObject *)
{
	std::cout << "SphereToSphere" << std::endl;
	return false;
}

bool CollisionManager::BoxToPlane(PhysicsObject *, PhysicsObject *)
{
	std::cout << "BoxToPlane" << std::endl;
	return false;
}

bool CollisionManager::BoxToSphere(PhysicsObject *, PhysicsObject *)
{
	std::cout << "BoxToSphere" << std::endl;
	return false;
}

bool CollisionManager::BoxToBox(PhysicsObject *, PhysicsObject *)
{
	std::cout << "BoxToBox" << std::endl;
	return false;
}