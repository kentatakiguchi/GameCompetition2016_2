#include "WeakEnemy.h"

WeakEnemy::WeakEnemy(IWorld * world, const Vector2& position) :
	BaseEnemy(world, position, 64.0f)
{
	BaseEnemy::Initialize();
}

void WeakEnemy::onMessage(EventMessage event, void *)
{
}

// 索敵時の行動です
void WeakEnemy::searchMove()
{
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::L))
		position_.x += 4.0f * deltaTimer_;
	else if (InputMgr::GetInstance().IsKeyOn(KeyCode::J))
		position_.x += -4.0f * deltaTimer_;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::I))
		position_.y += -4.0f * deltaTimer_;
	else if (InputMgr::GetInstance().IsKeyOn(KeyCode::K))
		position_.y += 4.0f * deltaTimer_;
	//BaseEnemy::searchMove();
	// 通常時の速度に戻す
	//speed_ = initSpeed_;
	//auto direction = 1;
	//if ((int)(stateTimer_ / 2.0f) % 2 == 1)
	//	direction = -1;
	//// 垂直移動
	//position_.y += -speed_ * direction;

	// ボックス移動
	//position_ += enemyManager_.boxMove() * speed_;
}

// 追跡時の行動です
void WeakEnemy::chaseMove()
{
	// 通常時よりも速めにする
	speed_ = initSpeed_ + 1.5f;
	auto point = position_ - player_->getPosition();
	// プレイヤーの軸付近に来たら止まる
	if (std::abs(point.x) < speed_ ||
		std::abs(point.y) < speed_) return;
	// 追跡
	position_ += enemyManager_.getPlayerNormalizeDirection() * -speed_;
	//// 垂直移動
	//position_ += position_.Up * -speed_ * BaseEnemy::playerDirection().y;
}
