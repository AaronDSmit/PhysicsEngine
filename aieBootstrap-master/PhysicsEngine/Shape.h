#ifndef Shape_H
#define Shape_H

#include "PhysicsObject.h"
#include <glm/glm.hpp>

namespace aie
{
	class Renderer2D;
}

/// <summary>
/// A child of Physics Object, this class holds an array of vertices used to describe the shape.
/// </summary> 

class Shape : public PhysicsObject
{
public:
	Shape() = delete;

	Shape(glm::vec2 position, glm::vec2* vertices, unsigned int numOfVertices, glm::vec4 colour);

	void setPosition(const glm::vec2 position) { m_position = position; }
	glm::vec2 getPosition() const { return m_position; }

	void setColour(const glm::vec4 colour) { m_colour = colour; }
	glm::vec4 getColour() const { return m_colour; }

	void fixedUpdate(glm::vec2 gravity, float deltaTime) override;

	void draw(class aie::Renderer2D* renderer) override final;

	~Shape() = default;

protected:

	// centre point of shape
	glm::vec2 m_position;

	// Clockwise points of the shape
	glm::vec2* m_vertices;

	unsigned int m_vertsCount;

	glm::vec4 m_colour;
};

#endif // !Shape_H