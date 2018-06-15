#ifndef RigidBody_H
#define RigidBody_H

#include <glm/glm.hpp>

enum ForceMode
{
	FORCE,
	ACCELERATION,
	IMPULSE,
	VELOCITYCHANGE
};

class RigidBody
{

protected:
	RigidBody() {};
public:

	RigidBody(class Shape* shape, glm::vec2 velocity, float mass);

	virtual void FixedUpdate(glm::vec2 gravity, float fixedDeltaTime);

	void ApplyForce(glm::vec2 force, ForceMode forceMode);

	void setPosition(glm::vec2 position);
	glm::vec2 getPosition() const { return m_position; }
	void Translate(glm::vec2 translation);

	glm::vec2 getVelocity() const { return m_velocity; }

	void setIsKinematic(bool isKinematic) { m_iskinematic = isKinematic; }
	bool isKinematic() const { return m_iskinematic; }

	void setMass(float mass) { m_mass = mass; }
	float getMass() const { return (m_iskinematic) ? INT_MAX : m_mass; }

	~RigidBody();

protected:
	glm::vec2 m_position;

	glm::vec2 m_acceleration;
	glm::vec2 m_velocity;

	float m_mass;

	bool m_iskinematic;

	class Shape* m_shape;
};

#endif // !RigidBody_H