#include "Collision.h"
#include "PhysicsObject.h"


Collision::Collision(PhysicsObject* _obj1, PhysicsObject* _obj2)
{
	obj1 = _obj1;
	obj2 = _obj2;

	obj1->OnCollisionEnter();
	obj2->OnCollisionEnter();
}

Collision::~Collision()
{
	obj1->OnCollisionExit();
	obj2->OnCollisionExit();
}