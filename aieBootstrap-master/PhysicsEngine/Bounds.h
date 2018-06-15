#ifndef Bounds_H
#define Bounds_H

#include <glm/glm.hpp>

namespace aie
{
	class Renderer2D;
}

/// <summary>
/// Used solely by the Quad Tree, this class represents a spatial partition of the screen.
/// </summary> 

class Bounds
{
public:
	Bounds();

	Bounds(glm::vec2 a_centre, glm::vec2 a_halfSize);

	void Draw(aie::Renderer2D* renderer);

	glm::vec2 centre;
	glm::vec2 halfSize;

	bool Contains(const Bounds& other) const;

	~Bounds() = default;
};

#endif // !Bounds_H