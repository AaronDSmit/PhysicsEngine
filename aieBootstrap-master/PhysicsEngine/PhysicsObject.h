#ifndef PhysicsObject_H
#define PhysicsObject_H

#include <memory>
#include <glm/glm.hpp>
#include "Spring.h"

namespace aie
{
	class Renderer2D;
}

/// <summary>
/// 
/// </summary> 

class PhysicsObject
{
public:
	PhysicsObject();

	virtual void fixedUpdate(glm::vec2 gravity, float deltaTime) = 0;

	virtual void draw(class aie::Renderer2D* renderer) = 0;

	void addRigidBody(std::unique_ptr<class RigidBody> rigidBody);
	void removeRigidBody();

	// Returns raw pointer to this objects unique_ptr. Don't delete
	class RigidBody* getRigidBody() const { return m_rigidBody.get(); }

	void addCollider(std::unique_ptr<class Collider> collider);
	void removeCollider();

	// Returns raw pointer to this objects unique_ptr. Don't delete
	class Collider* getCollider() const { return m_collider.get(); }

	void addSpring(std::unique_ptr<class Spring> spring);

	void setShatterThreshold(float force) { m_shatterThreshold = force; }
	float getShatterThreshold() const { return m_shatterThreshold; }

	bool isDynamic() const { return m_rigidBody != nullptr; }
	bool isStatic() const { return m_rigidBody == nullptr; }

	~PhysicsObject();

protected:
	std::unique_ptr<class RigidBody> m_rigidBody;
	std::unique_ptr<class Collider> m_collider;

	float m_shatterThreshold;
	std::unique_ptr<class Spring> m_joint;
};

#endif // !PhysicsObject_H