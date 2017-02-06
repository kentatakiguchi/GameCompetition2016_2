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
}

void FlyingMiniBoss::move(float deltaTime)
{
	// 移動
	deg_ += 2.5f * (deltaTime * 60.0f);
	//position_.x += speed_ * timer_  * 9.8f * (deltaTime * 60.0f);
	position_.x += direction_.x * speed_ * (deltaTime * 60.0f);
	position_.y -= 2.0f * MathHelper::Sin(deg_) * (deltaTime * 60.0f);
	setTexPosition(10.0f);
	animation_.changeDirType(direction_.x);

	//deg_ += (deltaTime * 60.0f);
	//position_.x += direction_.x * 50.0f * (deltaTime * 60.0f);
	////position_.y -= 2.0f * MathHelper::Sin(deg_) * (deltaTime * 60.0f);
	//
}

// 床に当たった時の処理
void FlyingMiniBoss::floorHit()
{
	if (isLeft_ || isRight_) {
		changeState(State::Dead, WAIT_NUMBER);
		// 位置の更新
		//setTexPosition(-50.0f);
		// 中点を下にする
		//orizin_ = Vector2::One * (256.0f / 2.0f) + Vector2::Up * 100.0f;
		// プレイヤーと逆の方向を向く
		//animation_.changeDirType(getPlayerDirection().x);
	}
}
