#include "TestColl.h"

TestColl::TestColl(IWorld * world, const Vector3 & position) :
	Actor(world, "TestColl", position, CollisionBase(Vector2(0, 0), Vector2(0, 0), Vector2(0, 0), Vector2(0, 0))) {

}

TestColl::~TestColl()
{
}

void TestColl::onUpdate(float deltaTime)
{
	Vector3 velocity_ = Vector3::Zero;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::L)) {
		velocity_.x = 1;
	}
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::J)) {
		velocity_.x = -1;
	}
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::I)) {
		velocity_.y = -1;
	}
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::K)) {
		velocity_.y = 1;
	}
	position_ += velocity_ * 5;

	Vector2 pos = Vector2(position_.x, position_.y);
	body_.transform(pos + Vector2(0, 0) * 100, pos + Vector2(1, 0) * 100, pos + Vector2(0, 1) * 100, pos + Vector2(1, 1) * 100);
}

void TestColl::onDraw() const{
	body_.draw();
}

void TestColl::onCollide(Actor & other){
	if (other.getName() == "Player") {
		int a = 0;
	}
	else if (other.getName() == "item") {
		int a = 0;
	}
}
