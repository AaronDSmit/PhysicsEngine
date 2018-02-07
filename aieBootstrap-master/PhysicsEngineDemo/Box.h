#ifndef Box_H
#define Box_H

#include "RigidBody.h"
#include <glm/glm.hpp>

class Box : public RigidBody
{
public:

	Box(glm::vec2 position, glm::vec2 velocity, float mass, float length, float height, glm::vec4 colour);

	virtual void MakeGizmo() override;

	virtual void Debug() override;

	Box() = delete;
	~Box();

protected:
	glm::vec4 m_colour;
	float m_length;
	float m_height;
};

#endif // !Box_H