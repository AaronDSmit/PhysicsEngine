#include "CollisionManager.h"
#include "PhysicsObject.h"
#include "RigidBody.h"
#include "Collider.h"
#include "QuadTree.h"
#include "PhysicsScene.h"

typedef Collision(*fn)(PhysicsObject* obj1, PhysicsObject* obj2);

static fn collisionFunctionArray[] =
{
	nullptr,		//Plane to Plane
	CollisionManager::planeToCircle,
	CollisionManager::planeToAABB,
	CollisionManager::circleToPlane,
	CollisionManager::circleToCircle,
	CollisionManager::circleToAABB,
	CollisionManager::AABBToPlane,
	CollisionManager::AABBToCircle,
	CollisionManager::AABBToAABB,
};

CollisionManager::CollisionManager(PhysicsScene* scene)
	: m_useQuadTree(false)
	, m_scene(scene)
{
	m_tree = std::make_unique<QuadTree>(0, Bounds(glm::vec2(1280.0f * 0.5f, 720.0f * 0.5f), glm::vec2(1280.0f * 0.5f, 720.0f * 0.5f)));
}

void CollisionManager::checkCollisions(std::vector<PhysicsObject*>& m_actors)
{
	if (m_useQuadTree)
	{
		m_tree->Clear();

		// Check for collisions for all objects
		for (auto actor1 : m_actors)
		{
			if (actor1->isDynamic())
			{
				m_tree->Insert(actor1);
			}
			else if (actor1->getCollider()->getType() == ColliderType::PLANE)
			{
				m_tree->Insert(actor1);
			}

			// Check collision
			m_objectList.clear();

			m_tree->Retrieve(m_objectList, actor1);

			for (auto actor2 : m_objectList)
			{
				int shapeID1 = actor1->getCollider()->getType();
				int shapeID2 = actor2->getCollider()->getType();

				int functionID = (shapeID1 * SHAPE_COUNT) + shapeID2;
				fn functionPtr = collisionFunctionArray[functionID];

				if (functionPtr != nullptr)
				{
					Collision data = functionPtr(actor1, actor2);

					if (data.collision)
					{
						seperateCollision(data, actor1, actor2);
						resolveCollision(data, actor1, actor2);
					}
				}
			}
		}

		return;
	}

	int actorCount = (int)m_actors.size();

	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];

			if (checkAABBCollisions(object1, object2) || object1->getCollider()->getType() == ColliderType::PLANE || object2->getCollider()->getType() == ColliderType::PLANE)
			{
				// If they're both AABB's then don't check further for collisions
				if (object1->getCollider()->getType() == ColliderType::AABB && object2->getCollider()->getType() == ColliderType::AABB)
				{
					Collision data = AABBToAABB(object1, object2);

					seperateCollision(data, object1, object2);
					resolveCollision(data, object1, object2);

					continue;
				}

				if (checkCircleCollisions(object1, object2) || object1->getCollider()->getType() == ColliderType::PLANE || object2->getCollider()->getType() == ColliderType::PLANE)
				{
					// If they're both circles's then don't check further for collisions
					if (object1->getCollider()->getType() == ColliderType::CIRLCE && object2->getCollider()->getType() == ColliderType::CIRLCE)
					{
						Collision data = circleToCircle(object1, object2);

						seperateCollision(data, object1, object2);
						resolveCollision(data, object1, object2);

						continue;
					}
				}

				// If either shape is a polygon use SAT, otherwise use look-up table
				if (object1->getCollider()->getType() == ColliderType::POLYGON || object2->getCollider()->getType() == ColliderType::POLYGON)
				{

					continue;
				}

				// Here is the lookup table collision check, will be between circle/aabb to plane

				int shapeID1 = object1->getCollider()->getType();
				int shapeID2 = object2->getCollider()->getType();

				int functionID = (shapeID1 * SHAPE_COUNT) + shapeID2;
				fn functionPtr = collisionFunctionArray[functionID];

				if (functionPtr != nullptr)
				{
					Collision data = functionPtr(object1, object2);

					if (data.collision)
					{
						seperateCollision(data, object1, object2);
						resolveCollision(data, object1, object2);
					}
				}
			}
		}

	}
}

void CollisionManager::draw(aie::Renderer2D* renderer)
{
	if (m_useQuadTree)
	{
		m_tree->Draw(renderer);
	}
}

Collision CollisionManager::planeToCircle(PhysicsObject* plane, PhysicsObject* circle)
{
	assert(plane->getCollider()->getType() == ColliderType::PLANE && circle->getCollider()->getType() == ColliderType::CIRLCE);

	if (circle->isStatic())
		return Collision(false);

	if (plane->getCollider()->getType() == ColliderType::PLANE && circle->getCollider()->getType() == ColliderType::CIRLCE)
	{
		glm::vec2 normal = plane->getCollider()->getNormal();

		float distanceBetween = glm::dot(circle->getRigidBody()->getPosition(), plane->getCollider()->getNormal()) - plane->getCollider()->getDistanceToOrigin();

		float overlap = circle->getCollider()->getRadius() - distanceBetween;

		if (overlap > 0)
		{
			return Collision(overlap, normal, true);
		}
	}

	return Collision(false);
}

Collision CollisionManager::planeToAABB(PhysicsObject* plane, PhysicsObject* AABB)
{
	assert(plane->getCollider()->getType() == ColliderType::PLANE && AABB->getCollider()->getType() == ColliderType::AABB);

	if (AABB->isStatic())
		return Collision(false);

	glm::vec2 normal = plane->getCollider()->getNormal();

	Collider* box = AABB->getCollider();

	float closestPosArry[4];

	closestPosArry[0] = glm::dot(box->getTL() - normal * plane->getCollider()->getDistanceToOrigin(), normal);
	closestPosArry[1] = glm::dot(box->getTR() - normal * plane->getCollider()->getDistanceToOrigin(), normal);
	closestPosArry[2] = glm::dot(box->getBL() - normal * plane->getCollider()->getDistanceToOrigin(), normal);
	closestPosArry[3] = glm::dot(box->getBR() - normal * plane->getCollider()->getDistanceToOrigin(), normal);

	float closestPoint = closestPosArry[0];
	int closestIndex = 0;

	for (int i = 1; i < 3; i++)
	{
		if (closestPosArry[i] < closestPoint)
		{
			closestPoint = closestPosArry[i];
			closestIndex = i;
		}
	}

	if (closestPosArry[closestIndex] < 0)
	{
		return Collision(-closestPosArry[closestIndex], normal, true);
	}


	return Collision(false);
}

Collision CollisionManager::circleToPlane(PhysicsObject* circle, PhysicsObject* plane)
{
	return planeToCircle(plane, circle);
}

float Clamp(float val, float min, float max)
{
	return glm::max(min, glm::max(max, val));
}


Collision CollisionManager::circleToAABB(PhysicsObject* circle, PhysicsObject* AABB)
{
	assert(circle->getCollider()->getType() == ColliderType::CIRLCE && AABB->getCollider()->getType() == ColliderType::AABB);

	// Check if the centre point of the circle is within the AABB
	if (circle->getCollider()->getPosition().x < AABB->getCollider()->getBR().x
		&& circle->getCollider()->getPosition().x > AABB->getCollider()->getBL().x
		&& circle->getCollider()->getPosition().y < AABB->getCollider()->getTR().y
		&& circle->getCollider()->getPosition().y > AABB->getCollider()->getBR().y
		)
	{
		glm::vec2 vecBetween = AABB->getCollider()->getPosition() - circle->getCollider()->getPosition();

		if (vecBetween.x != 0.0f && vecBetween.y != 0.0f)
		{
			return Collision(2.0f, vecBetween, true);
		}

		// Possibly could ignore the collision of the two object's centre points are at the same position.
		// currently the result is to push the circle to the right, simply to get the circle centre out of the aabb
		return Collision(2.0f, { 1.0f, 0.0f }, true);
	}

	glm::vec2 vecBetween = circle->getCollider()->getPosition() - AABB->getCollider()->getPosition();

	glm::vec2 offset = { glm::dot(vecBetween,{ 1.0f,0.0f }),glm::dot(vecBetween,{ 0.0f,1.0f }) };

	Collider* box = AABB->getCollider();

	if (glm::abs(offset.x) > (box->getExtents().x * 0.5f))
	{
		offset.x = (box->getExtents().x) * ((offset.x > 0) ? 1.0f : -1.0f);
	}
	if (glm::abs(offset.y) > (box->getExtents().y * 0.5f))
	{
		offset.y = (box->getExtents().y) * ((offset.y > 0) ? 1.0f : -1.0f);
	}

	offset += AABB->getCollider()->getPosition();

	glm::vec2 vecBetweenClamped = offset - circle->getCollider()->getPosition();

	if (vecBetweenClamped.x == 0.0f && vecBetweenClamped.y == 0.0f)
	{
		return Collision(false);
	}

	if (glm::length(vecBetweenClamped) < circle->getCollider()->getRadius())
	{
		float depth = glm::length(vecBetweenClamped) - circle->getCollider()->getRadius();
		glm::vec2 normal = glm::normalize(vecBetweenClamped);

		return Collision(depth, -normal, true);
	}

	return Collision(false);
}

Collision CollisionManager::circleToCircle(PhysicsObject* circle1, PhysicsObject* circle2)
{
	assert(circle1->getCollider()->getType() == ColliderType::CIRLCE && circle2->getCollider()->getType() == ColliderType::CIRLCE);

	float distBetween = glm::distance(circle2->getCollider()->getPosition(), circle1->getCollider()->getPosition());

	float totalRadiusDist = circle1->getCollider()->getRadius() + circle2->getCollider()->getRadius();
	totalRadiusDist *= totalRadiusDist;

	glm::vec2 normal = glm::normalize(circle2->getCollider()->getPosition() - circle1->getCollider()->getPosition());

	float xSquared = circle2->getCollider()->getPosition().x - circle1->getCollider()->getPosition().x;
	xSquared *= xSquared;

	float ySquared = circle2->getCollider()->getPosition().y - circle1->getCollider()->getPosition().y;
	ySquared *= ySquared;

	if ((xSquared + ySquared) < totalRadiusDist)
	{
		glm::vec2 vecBetween = circle2->getCollider()->getPosition() - circle1->getCollider()->getPosition();

		float depth = ((circle1->getCollider()->getRadius() + circle2->getCollider()->getRadius()) - glm::length(vecBetween));
		return Collision(depth, normal, true);
	}

	return Collision(false);
}

Collision CollisionManager::AABBToPlane(PhysicsObject* AABB, PhysicsObject* plane)
{
	return planeToAABB(plane, AABB);
}

Collision CollisionManager::AABBToCircle(PhysicsObject* AABB, PhysicsObject* circle)
{
	Collision collData = circleToAABB(circle, AABB);
	collData.normal *= -1.0f;

	return collData;
}

Collision CollisionManager::AABBToAABB(PhysicsObject* AABB1, PhysicsObject* AABB2)
{
	assert(AABB1->getCollider()->getType() == ColliderType::AABB && AABB2->getCollider()->getType() == ColliderType::AABB);

	float offsetFaceDis = 0.0f;

	Collider* box1 = AABB1->getCollider();
	Collider* box2 = AABB2->getCollider();

	if (box1->getBL().x < box2->getTR().x
		&& box1->getTR().x > box2->getBL().x
		&& box1->getBL().y < box2->getTR().y
		&& box1->getTR().y > box2->getBL().y)
	{
		glm::vec2 xOverlap1 = { box1->getTR().x - box2->getBL().x, 0.0f };
		glm::vec2 xOverlap2 = { box1->getBL().x - box2->getTR().x, 0.0f };

		glm::vec2 yOverlap1 = { 0.0f, box1->getTR().y - box2->getBL().y };
		glm::vec2 yOverlap2 = { 0.0f, box1->getBL().y - box2->getTR().y };

		float lowestDist = glm::abs(xOverlap1.x);
		glm::vec2 lowestVec = xOverlap1;

		if (abs(xOverlap2.x) < lowestDist)
		{
			lowestDist = abs(xOverlap2.x);
			lowestVec = xOverlap2;
		}

		if (abs(yOverlap1.y) < lowestDist)
		{
			lowestDist = abs(yOverlap1.y);
			lowestVec = yOverlap1;
		}

		if (abs(yOverlap2.y) < lowestDist)
		{
			lowestDist = abs(yOverlap2.y);
			lowestVec = yOverlap2;
		}

		return Collision(lowestDist, glm::normalize(lowestVec), true);
	}

	return Collision(false);
}

void CollisionManager::seperateCollision(const Collision collision, PhysicsObject* obj1, PhysicsObject* obj2)
{
	float moveRatio1 = (obj1->isDynamic() && obj2->isStatic()) ? 1.0f : 0.0f;
	float moveRatio2 = (obj2->isDynamic() && obj1->isStatic()) ? 1.0f : 0.0f;

	if (obj1->isDynamic() && obj2->isDynamic())
	{
		float totalMass = obj1->getRigidBody()->getMass() + obj2->getRigidBody()->getMass();

		moveRatio1 = 1 - obj1->getRigidBody()->getMass() / totalMass;
		moveRatio2 = 1 - obj2->getRigidBody()->getMass() / totalMass;
	}

	if (obj1->isDynamic())
	{
		obj1->getRigidBody()->Translate(-collision.normal * moveRatio1 * collision.depth);
	}

	if (obj2->isDynamic())
	{
		obj2->getRigidBody()->Translate(collision.normal * moveRatio2 * collision.depth);
	}
}

void CollisionManager::resolveCollision(const Collision collData, PhysicsObject* obj1, PhysicsObject* obj2)
{
	glm::vec2 normal = collData.normal;
	glm::vec2 relativeVelocity = { 0.0f, 0.0f };
	float elasticity = 1.0f;

	float inverseMass1 = (obj1->isDynamic()) ? (1 / obj1->getRigidBody()->getMass()) : 0.0f;
	float inverseMass2 = (obj2->isDynamic()) ? (1 / obj2->getRigidBody()->getMass()) : 0.0f;

	if (obj1->isDynamic() && obj2->isDynamic())
	{
		// Exit early if normal is not a number
		if (normal.x != normal.x && normal.y != normal.y)
			return;

		normal = glm::normalize(obj2->getRigidBody()->getPosition() - obj1->getRigidBody()->getPosition());

		if (!obj1->getRigidBody()->isKinematic() && !obj2->getRigidBody()->isKinematic())
		{
			relativeVelocity = obj2->getRigidBody()->getVelocity() - obj1->getRigidBody()->getVelocity();

			if (m_shatter)
			{
				if (glm::length(relativeVelocity) > obj1->getShatterThreshold())
				{
					m_scene->ShatterObject(obj1, { 0.0f, 0.0f });
				}

				if (glm::length(relativeVelocity) > obj2->getShatterThreshold())
				{
					m_scene->ShatterObject(obj2, { 0.0f, 0.0f });
				}
			}
		}
		else if (!obj1->getRigidBody()->isKinematic())
		{
			relativeVelocity = obj1->getRigidBody()->getVelocity();

			if (m_shatter && glm::length(relativeVelocity) > obj1->getShatterThreshold())
			{
				m_scene->ShatterObject(obj1, { 0.0f, 0.0f });
			}
		}
		else
		{
			relativeVelocity = obj2->getRigidBody()->getVelocity();

			if (m_shatter && glm::length(relativeVelocity) > obj2->getShatterThreshold())
			{
				m_scene->ShatterObject(obj2, { 0.0f, 0.0f });
			}
		}

		float j = glm::dot(-(1 + elasticity) * relativeVelocity, normal)
			/ glm::dot(normal, normal * (inverseMass1 + inverseMass2));

		glm::vec2 force = normal * j;

		obj1->getRigidBody()->ApplyForce(-force, ForceMode::IMPULSE);
		obj2->getRigidBody()->ApplyForce(force, ForceMode::IMPULSE);
	}
	else if (obj1->isStatic() && obj2->isDynamic())
	{
		relativeVelocity = obj2->getRigidBody()->getVelocity();

		float j = (-(1 + elasticity) * glm::dot(relativeVelocity, normal)) / 1.0f / inverseMass2;

		glm::vec2 force = normal * j;
		obj2->getRigidBody()->ApplyForce(force, ForceMode::IMPULSE);
	}
	else if (obj2->isStatic() && obj1->isDynamic())
	{
		relativeVelocity = obj1->getRigidBody()->getVelocity();

		float j = (-(1 + elasticity) * glm::dot(relativeVelocity, normal)) / inverseMass1;

		glm::vec2 force = normal * j;
		obj1->getRigidBody()->ApplyForce(force, ForceMode::IMPULSE);
	}
}

bool CollisionManager::checkAABBCollisions(PhysicsObject* obj1, PhysicsObject* obj2) const
{
	bool iscollision = obj1->getCollider()->getBL().x < obj2->getCollider()->getTR().x
		&& obj1->getCollider()->getTR().x > obj2->getCollider()->getBL().x
		&& obj1->getCollider()->getBL().y < obj2->getCollider()->getTR().y
		&& obj1->getCollider()->getTR().y > obj2->getCollider()->getBL().y;

	if (iscollision)
	{
		return true;
	}

	return false;
}

bool CollisionManager::checkCircleCollisions(PhysicsObject* obj1, PhysicsObject* obj2) const
{
	float overlap = glm::distance(obj1->getCollider()->getPosition(), obj2->getCollider()->getPosition()) - (obj1->getCollider()->getRadius() + obj2->getCollider()->getRadius());

	if (overlap < 0)
	{
		return true;
	}

	return false;
}
