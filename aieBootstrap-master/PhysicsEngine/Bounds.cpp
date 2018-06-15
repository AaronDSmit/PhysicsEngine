#include "Bounds.h"

#include "Renderer2D.h"

Bounds::Bounds()
	: centre({ 0.0f, 0.0f })
	, halfSize({ 0.0f, 0.0f })
{

}

Bounds::Bounds(glm::vec2 a_centre, glm::vec2 a_halfSize)
	: centre(a_centre)
	, halfSize(a_halfSize)
{

}

void Bounds::Draw(aie::Renderer2D* a_renderer)
{
	a_renderer->setRenderColour(1.0f, 1.0f, 1.0f);

	// Draw Left side
	a_renderer->drawLine(centre.x - halfSize.x, centre.y - halfSize.y, centre.x - halfSize.x, centre.y + halfSize.y);

	// Draw Right side
	a_renderer->drawLine(centre.x + halfSize.x, centre.y - halfSize.y, centre.x + halfSize.x, centre.y + halfSize.y);

	// Draw top side
	a_renderer->drawLine(centre.x - halfSize.x, centre.y + halfSize.y, centre.x + halfSize.x, centre.y + halfSize.y);

	// Draw bottom side
	a_renderer->drawLine(centre.x - halfSize.x, centre.y - halfSize.y, centre.x + halfSize.x, centre.y - halfSize.y);
}

bool Bounds::Contains(const Bounds& other) const
{
	// left side less than box.left side and right side greater than box.right side
	if (centre.x - halfSize.x < other.centre.x - other.halfSize.x && centre.x + halfSize.x > other.centre.x + other.halfSize.x)
	{
		// bottom side less than box.bottom side and top side greater than box.top side
		if (centre.y - halfSize.y < other.centre.y - other.halfSize.y && centre.y + halfSize.y > other.centre.y + other.halfSize.y)
		{
			return true;
		}
	}

	return false;
}
