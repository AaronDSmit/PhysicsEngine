#ifndef Collision_H
#define Collision_H

#include <glm/glm.hpp>

class Collision
{
public:

	Collision(class PhysicsObject* _obj1, class PhysicsObject* _obj2);
	
	class PhysicsObject* obj1;
	class PhysicsObject* obj2;
	float penetration;
	glm::vec2 normal;

	~Collision();
};

#endif // !Collision_H