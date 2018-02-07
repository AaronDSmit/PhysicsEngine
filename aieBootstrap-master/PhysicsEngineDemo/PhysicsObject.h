#ifndef PhysicsObject_H
#define PhysicsObject_H

#include <glm/glm.hpp>

enum  ShapeType
{
	PLANE = 0,
	SPHERE,
	BOX,
	SHAPE_COUNT
};

class PhysicsObject
{
protected:
	PhysicsObject(ShapeType _shapeID) : m_shapeID(_shapeID) {}

public:

	virtual void FixedUpdate(glm::vec2 gravity, float fixedDeltaTime) = 0;
	virtual void Debug() = 0;
	virtual void MakeGizmo() = 0;
	virtual void ResetPosition() {};
	ShapeType GetShapeID() { return m_shapeID; }

	virtual void OnCollisionEnter() = 0;
	virtual void OnCollision() = 0;
	virtual void OnCollisionExit() = 0;

protected:
	ShapeType m_shapeID;
};

#endif // !PhysicsObject_H
