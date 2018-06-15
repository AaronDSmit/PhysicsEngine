#ifndef QuadTree_H
#define QuadTree_H

#include <vector>
#include <glm/glm.hpp>
#include "Bounds.h"

namespace aie
{
	class Renderer2D;
}

/// <summary>
/// Used by the Collision Manager to partition the screen into 4 equal nodes. Will split nodes when they reach capacity. 
/// IT can return an array of all objects within the same node as a given object.
/// </summary> 

class QuadTree
{
public:
	QuadTree();

	// Overloaded Constructor that takes in int level and BoxCollider
	QuadTree(const int a_level, const Bounds& a_bounds);

	// Clears the QuadTree of all nodes
	void Clear();

	// Split the node into 4 sub nodes
	void Split();

	// Insert 
	void Insert(class PhysicsObject* a_object);

	void Draw(aie::Renderer2D* renderer);

	// Return all objects that could collide with given object
	void Retrieve(std::vector<class PhysicsObject*>& returnList, const class PhysicsObject* a_object) const;

	~QuadTree();

private:
	unsigned int m_maxObjects;
	unsigned int m_maxLevels;

	unsigned int m_objectCount;

	unsigned int m_level;

	std::vector<class PhysicsObject*> m_objects;

	Bounds m_bounds;

	QuadTree* nodes[4];

	/*
	* Determine which node the object belongs to. -1 means
	* object cannot completely fit within a child node and is part
	* of the parent node
	*/

	int getIndex(const class PhysicsObject* a_object) const;
};

#endif // !QuadTree_H