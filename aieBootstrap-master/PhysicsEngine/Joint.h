#ifndef Joint_H
#define Joint_H

#include <glm/glm.hpp>

namespace aie
{
	class Renderer2D;
}

/// <summary>
/// A connection between to RigidBodies
/// </summary> 

class Joint
{
protected:

	Joint();

public:

	Joint(class RigidBody* body1, class RigidBody* body2);

	virtual void FixedUpdate(glm::vec2 gravity, float fixedDeltaTime) = 0;

	virtual void draw(class aie::Renderer2D* renderer);

	~Joint() = default;

protected:
	class RigidBody* m_body1;
	class RigidBody* m_body2;
};

#endif // !Joint_H