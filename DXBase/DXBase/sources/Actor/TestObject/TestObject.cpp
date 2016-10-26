#include "TestObject.h"
#include "../../Game/Time.h"
TestObject::TestObject(IWorld * world, const Vector3 & position):
	Actor(world, "Object", position, CollisionBase())
{
	position_ = Vector3::Zero;
}

TestObject::~TestObject()
{
}

void TestObject::onUpdate(float deltaTime)
{
	position_.x += 200.0f*Time::GetInstance().deltaTime();
}

void TestObject::onDraw() const
{
	DrawCircle(position_.x, position_.y, 20, GetColor(255, 0, 0), true, true);
}

void TestObject::onCollide(Actor & other)
{
}
