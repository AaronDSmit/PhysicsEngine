#include "QuadTree.h"
#include "PhysicsObject.h"
#include "Collider.h"

QuadTree::QuadTree()
	: m_maxObjects(3)
	, m_maxLevels(5)
	, m_objectCount(0)
	, m_level(0)
{

}

QuadTree::QuadTree(const int a_level, const Bounds& a_bounds)
	: m_maxObjects(3)
	, m_maxLevels(3)
	, m_objectCount(0)
	, m_level(a_level)
	, m_bounds(a_bounds)
{
	for (int i = 0; i < 4; i++)
	{
		nodes[i] = nullptr;
	}
}

void QuadTree::Clear()
{
	if (m_objects.size() > 0)
	{
		m_objects.clear();
	}

	if (nodes[0] != nullptr)
	{
		nodes[0]->Clear();
		nodes[1]->Clear();
		nodes[2]->Clear();
		nodes[3]->Clear();
	}
}

void QuadTree::Split()
{
	nodes[0] = new QuadTree(m_level + 1, Bounds(glm::vec2(m_bounds.centre.x - m_bounds.halfSize.x / 2, m_bounds.centre.y + m_bounds.halfSize.y / 2), glm::vec2(m_bounds.halfSize.x / 2, m_bounds.halfSize.y / 2)));
	nodes[1] = new QuadTree(m_level + 1, Bounds(glm::vec2(m_bounds.centre.x + m_bounds.halfSize.x / 2, m_bounds.centre.y + m_bounds.halfSize.y / 2), glm::vec2(m_bounds.halfSize.x / 2, m_bounds.halfSize.y / 2)));
	nodes[2] = new QuadTree(m_level + 1, Bounds(glm::vec2(m_bounds.centre.x + m_bounds.halfSize.x / 2, m_bounds.centre.y - m_bounds.halfSize.y / 2), glm::vec2(m_bounds.halfSize.x / 2, m_bounds.halfSize.y / 2)));
	nodes[3] = new QuadTree(m_level + 1, Bounds(glm::vec2(m_bounds.centre.x - m_bounds.halfSize.x / 2, m_bounds.centre.y - m_bounds.halfSize.y / 2), glm::vec2(m_bounds.halfSize.x / 2, m_bounds.halfSize.y / 2)));
}

void QuadTree::Insert(PhysicsObject* a_object)
{
	// If children exist, add it to the respective child
	if (nodes[0] != nullptr)
	{
		int index = getIndex(a_object);

		if (index != -1)
		{
			nodes[index]->Insert(a_object);

			return;
		}
	}

	// if no children exist, add it to this Node
	m_objects.push_back(a_object);
	m_objectCount++;

	if (m_objects.size() > m_maxObjects && m_level < m_maxLevels)
	{
		// if at capacity and have no children, split 
		if (nodes[0] == nullptr)
		{
			Split();
		}

		unsigned int i = 0;

		while (i < m_objects.size())
		{
			int index = getIndex(m_objects[i]);

			if (index != -1)
			{
				nodes[index]->Insert(m_objects[i]);
				m_objects.erase(m_objects.begin() + i);
			}
			else
			{
				i++;
			}
		}
	}
}

void QuadTree::Draw(aie::Renderer2D* renderer)
{
	m_bounds.Draw(renderer);

	((nodes[0] != nullptr) ? nodes[0]->Draw(renderer) : false);
	((nodes[1] != nullptr) ? nodes[1]->Draw(renderer) : false);
	((nodes[2] != nullptr) ? nodes[2]->Draw(renderer) : false);
	((nodes[3] != nullptr) ? nodes[3]->Draw(renderer) : false);
}

void QuadTree::Retrieve(std::vector<class PhysicsObject*>& returnList, const PhysicsObject * a_object) const
{
	int index = getIndex(a_object);

	// if object is entirely in child node
	if (index != -1)
	{
		nodes[index]->Retrieve(returnList, a_object);
	}

	for (unsigned int x = 0; x < m_objects.size(); x++)
	{
		if (m_objects[x] != a_object)
		{
			returnList.push_back(m_objects[x]);
		}
	}
}

QuadTree::~QuadTree()
{

}

int QuadTree::getIndex(const PhysicsObject* a_object) const
{
	if (nodes[0] != nullptr)
	{
		// If object is entirely in child 0

		if (nodes[0]->m_bounds.Contains(Bounds(a_object->getCollider()->getPosition(), a_object->getCollider()->getExtents())))
		{
			return 0;
		}

		// If object is entirely in child 1
		if (nodes[1]->m_bounds.Contains(Bounds(a_object->getCollider()->getPosition(), a_object->getCollider()->getExtents())))
		{
			return 1;
		}

		// If object is entirely in child 2
		if (nodes[2]->m_bounds.Contains(Bounds(a_object->getCollider()->getPosition(), a_object->getCollider()->getExtents())))
		{
			return 2;
		}

		// If object is entirely in child 3
		if (nodes[3]->m_bounds.Contains(Bounds(a_object->getCollider()->getPosition(), a_object->getCollider()->getExtents())))
		{
			return 3;
		}
	}

	return -1;
}
