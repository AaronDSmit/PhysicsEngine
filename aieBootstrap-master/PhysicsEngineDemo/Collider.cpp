#include "Collider.h"

Collider::Collider(ColliderType _type) : type(_type)
{

}

bool Collider::Intercepts(Collider* other)
{
	int functionId = other->GetType();

	return false;
}

bool Collider::Contains(Collider* other)
{
	int functionId = other->GetType();

	return false;
}

Collider::~Collider()
{

}