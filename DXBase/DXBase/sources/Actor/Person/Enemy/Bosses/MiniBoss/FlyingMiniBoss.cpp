#include "FlyingMiniBoss.h"
#include "ImportAnimationNumber.h"

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
	position_ += speed_ * prevPlayerDirection_ * (deltaTime * 60.0f);

	addTexPos_ = Vector2::Up * 10.0f;
	animation_.changeDirType(prevPlayerDirection_.x);
}

// 床に当たった時の処理
void FlyingMiniBoss::floorHit()
{
	//changeState(State::Dead, WAIT_NUMBER);
	if (state_ == State::Dead) return;
	changeDeadState(DeadState::HitDead, WAIT_NUMBER);
}

// プレイヤーの攻撃に当たった時の処理
void FlyingMiniBoss::playerAttackHit()
{
	changeDeadState(DeadState::HitDead, DEAD_NUMBER);
	body_.enabled(false);
}
