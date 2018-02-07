#ifndef Collider_H
#define Collider_H

#include <glm/glm.hpp>

enum  ColliderType
{
	PLANE = 0,
	SPHERE,
	BOX,
	SHAPE_COUNT
};

class Collider
{
public:
	Collider(ColliderType _type);

	Collider() = delete;

	void SetPosition(glm::vec2 actorPosition) { position = actorPosition; }

	virtual bool Intercepts(Collider* other);
	virtual bool Contains(Collider* other);

	ColliderType GetType() { return type; }

	~Collider();

protected:
	ColliderType type;
	glm::vec2 position;
};

#endif // !Collider_H