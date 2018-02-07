#include "Collision.h"
#include "PhysicsObject.h"


Collision::Collision(PhysicsObject* _obj1, PhysicsObject* _obj2)
{
	obj1 = _obj1;
	obj2 = _obj2;

	obj1->OnCollisionEnter(obj2);
	obj2->OnCollisionEnter(obj1);
}

Collision::~Collision()
{
	if (obj1 != nullptr)
	{
		obj1->OnCollisionExit(obj2);
	}

	if (obj2 != nullptr)
	{
		obj2->OnCollisionExit(obj1);
	}
}