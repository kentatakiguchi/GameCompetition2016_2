#include "FlyingMiniBoss.h"

FlyingMiniBoss::FlyingMiniBoss(
	IWorld * world,
	const Vector2 & position,
	const Vector2 & direction,
	const float bodyScale) :
	AdhereMiniBoss(world, position, bodyScale),
	deg_(0.0f)
{
	direction_ = direction;
	speed_ = 6.0f;
}

void FlyingMiniBoss::move(float deltaTime)
{
	// 移動
	//deg_ += 2.5f * (deltaTime * 60.0f);
	//position_.x += speed_ * timer_  * 9.8f * (deltaTime * 60.0f);
	//position_.x += direction_.x * speed_ * (deltaTime * 60.0f);
	//position_.y -= 2.0f * MathHelper::Sin(deg_) * (deltaTime * 60.0f);
	position_ += speed_ * prevPlayerDirection_ * (deltaTime * 60.0f);

	setTexPosition(10.0f);
	animation_.changeDirType(prevPlayerDirection_.x);
}

// 床に当たった時の処理
void FlyingMiniBoss::floorHit()
{
	changeState(State::Dead, WAIT_NUMBER);
}
