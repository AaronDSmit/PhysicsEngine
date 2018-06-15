#ifndef Spring_H
#define Spring_H

#include "Joint.h"
#include <glm/glm.hpp>

namespace aie
{
	class Renderer2D;
}

/// <summary>
/// A connection between to RigidBodies that behaves similar to a spring.
/// </summary> 

class Spring : Joint
{
public:

	Spring() = delete;

	Spring(RigidBody* body1, RigidBody* body2, float restLength, float springCoefficent, float damping = 0.1f);

	void FixedUpdate(glm::vec2 gravity, float fixedDeltaTime) override;

	void draw(class aie::Renderer2D* renderer) override;

	~Spring();

protected:

	float m_damping;
	float m_restLength;
	float m_springCoefficent; // restoring factor
};

#endif // !Spring_H