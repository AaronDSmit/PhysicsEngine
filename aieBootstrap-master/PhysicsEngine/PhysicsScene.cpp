#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "Collider.h"

#include "PhysicsObject.h"
#include "RigidBody.h"
#include "Shape.h"
#include "Spring.h"

#include <algorithm>
#include <cmath>
#include <glm/ext.hpp>
#include <iostream>
#include <memory>
#include "imgui.h"

void PhysicsScene::HandleInput()
{
	if (m_input->wasMouseButtonPressed(0))
	{
		addCircle({ m_input->getMouseX() , m_input->getMouseY() }, 20.0f, { 1.0f, 1.0f, 1.0f, 1.0f }, false, { 0.0f, 0.0f }, 10.0f);
	}

	if (m_input->wasMouseButtonPressed(1))
	{
		addAABB({ m_input->getMouseX() , m_input->getMouseY() }, { 20.0f, 20.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, false, { 0.0f, 0.0f }, 10.0f);
	}
}

PhysicsScene::PhysicsScene()
	:m_gravity({ 0.0f, -9.8f })
	, m_timeStep(0.01f)
	, m_backgroundColour({ 0.2f, 0.2f, 0.2f, 1.0f })
	, m_input(aie::Input::getInstance())
{
	m_collisionManager = std::make_unique<CollisionManager>(this);

	// Floor
	addPlane({ 0.0f, 1.0f }, 10.0f);

	// Left Wall
	addPlane({ 1.0f, 0.0f }, 10.0f);

	// Right wall
	addPlane({ -1.0f, 0.0f }, -1270.0f);

	// Right wall
	addPlane({ 0.75f, 0.75f }, 200.0f);

	// Ceiling
	addPlane({ 0.0f, -1.0f }, -710.0f);

	// Static Tests
	addCircle({ 400.0f, 200.0f }, 25, { 1.0f, 1.0f, 1.0f, 1.0f }, true);

	addAABB({ 400.0f, 100.0f }, { 20.0f, 20.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);

	// Dynamic Tests

	addCircle({ 100.0f, 600.0f }, 25, { 1.0f, 1.0f, 1.0f, 1.0f }, false);

	addAABB({ 200.0f, 600.0f }, { 20.0f, 20.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, false);

	// Circle to Circle Test
	addCircle({ 700.0f, 200.0f }, 25, { 1.0f, 1.0f, 1.0f, 1.0f }, false);
	addCircle({ 700.0f, 100.0f }, 25, { 1.0f, 1.0f, 1.0f, 1.0f }, false);

	// Circle to AABB Test
	addCircle({ 800.0f, 200.0f }, 25, { 1.0f, 1.0f, 1.0f, 1.0f }, false);
	addAABB({ 800.0f, 100.0f }, { 20.0f, 20.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, false);

	// AABB to AABB Test
	addAABB({ 900.0f, 200.0f }, { 20.0f, 20.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, false);
	addAABB({ 900.0f, 100.0f }, { 20.0f, 20.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, false);
}

PhysicsScene::PhysicsScene(const PhysicsScene &)
{

}

void PhysicsScene::Update(float deltaTime)
{
	HandleInput();

	FixedUpdate(deltaTime);
}

void PhysicsScene::FixedUpdate(float deltaTime)
{
	static float accumulatedTime = 0.0f;
	accumulatedTime += deltaTime;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto actor : m_actors)
		{
			if (actor->isDynamic())
			{
				actor->fixedUpdate(m_gravity, deltaTime);
			}
		}

		accumulatedTime -= m_timeStep;
	}

	m_collisionManager->checkCollisions(m_actors);
}

void PhysicsScene::addActor(PhysicsObject* actor)
{
	assert(actor != nullptr);
	assert(std::find(std::begin(m_actors), std::end(m_actors), actor) == m_actors.end());

	m_actors.push_back(actor);
}

void PhysicsScene::RemoveActor(PhysicsObject* actor)
{
	std::remove(std::begin(m_actors), std::end(m_actors), actor);
}

void PhysicsScene::addCircle(glm::vec2 position, float radius, glm::vec4 colour, bool isKinematic, glm::vec2 velocity, float mass)
{
	glm::vec2* verts = new glm::vec2[32];

	float rotDelta = glm::pi<float>() * 2.0f / 32.0f;

	for (unsigned int i = 0; i < 32; i++)
	{
		verts[i] = { glm::sin(rotDelta * i) * radius  , glm::cos(rotDelta * i) * radius };
	}

	Shape* circle = new Shape(position, verts, 32, colour);
	std::unique_ptr<Collider> collider = std::make_unique<Collider>(ColliderType::CIRLCE, circle, radius);

	circle->addCollider(std::move(collider));

	std::unique_ptr<RigidBody> rb = std::make_unique<RigidBody>(circle, velocity, mass);
	rb->setIsKinematic(isKinematic);
	circle->addRigidBody(std::move(rb));

	addActor(circle);
}

void PhysicsScene::addPlane(glm::vec2 normal, float distanceToOrigin, glm::vec4 colour)
{
	normal = glm::normalize(normal);

	float lineSegment = 2000.0f;

	glm::vec2 centrePoint = normal * distanceToOrigin;

	glm::vec2 parallel(normal.y, -normal.x);

	glm::vec2* verts = new glm::vec2[2];

	verts[0] = centrePoint + (parallel * lineSegment);
	verts[1] = centrePoint - (parallel * lineSegment);

	Shape* plane = new Shape({ 0.0f, 0.0f }, verts, 2, colour);
	std::unique_ptr<Collider> collider = std::make_unique<Collider>(ColliderType::PLANE, plane, normal, distanceToOrigin);
	plane->addCollider(std::move(collider));

	addActor(plane);
}

void PhysicsScene::addAABB(glm::vec2 position, glm::vec2 extents, glm::vec4 colour, bool isKinematic, glm::vec2 velocity, float mass)
{
	glm::vec2* verts = new glm::vec2[4];

	verts[0] = { -extents.x, -extents.y }; // bottom left
	verts[1] = { -extents.x, +extents.y }; // top left
	verts[2] = { +extents.x, +extents.y }; // top right
	verts[3] = { +extents.x, -extents.y }; // bottom right

	Shape* aabb = new Shape(position, verts, 4, colour);
	std::unique_ptr<Collider> collider = std::make_unique<Collider>(ColliderType::AABB, aabb, extents);

	aabb->addCollider(std::move(collider));
	std::unique_ptr<RigidBody> rb = std::make_unique<RigidBody>(aabb, velocity, mass);
	rb->setIsKinematic(isKinematic);
	aabb->addRigidBody(std::move(rb));

	addActor(aabb);
}

void PhysicsScene::addPolyon(glm::vec2 position, glm::vec2* verts, unsigned int vertCount, glm::vec4 colour, bool isKinematic, glm::vec2 velocity, float mass)
{
	Shape* polygon = new Shape(position, verts, vertCount, colour);

	std::unique_ptr<Collider> collider = std::make_unique<Collider>(ColliderType::POLYGON, polygon, verts);
	polygon->addCollider(std::move(collider));

	std::unique_ptr<RigidBody> rb = std::make_unique<RigidBody>(polygon, velocity, mass);
	rb->setIsKinematic(isKinematic);
	polygon->addRigidBody(std::move(rb));

	addActor(polygon);
}

void PhysicsScene::addSpring(PhysicsObject* object1, PhysicsObject* object2, float restLength, float springCoefficent, float damping)
{
	if (object1->isDynamic() && object2->isDynamic())
	{
		std::unique_ptr<Spring> spring = std::make_unique<Spring>(object1->getRigidBody(), object2->getRigidBody(), restLength, springCoefficent, damping);

		object1->addSpring(std::move(spring));
	}
}

void PhysicsScene::ShatterObject(PhysicsObject* object, glm::vec2 contactPoint)
{

}

void PhysicsScene::Draw(aie::Renderer2D* renderer)
{
	for (auto actor : m_actors)
	{
		actor->draw(renderer);
	}

	m_collisionManager->draw(renderer);

	// Use ImGui functions between here and Render()
	ImGui::NewFrame();

	// This creates a window
	ImGui::Begin("");
	ImGui::SetWindowPos(ImVec2(1100.0f, 0.0f));
	ImGui::Text("Left Click - Circle");
	ImGui::Text("Right Click - AABB");

	ImGui::End();

	// ImGui functions end here
	ImGui::Render();
}

PhysicsScene::~PhysicsScene()
{
	for (auto actor : m_actors)
	{
		delete actor;
	}
}