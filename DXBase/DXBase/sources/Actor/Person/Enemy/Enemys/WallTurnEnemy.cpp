#include "WallTurnEnemy.h"
#include "../../../Base/ActorGroup.h"
#include "../FloorSearchPoint.h"
#include "Prickle.h"

WallTrunEnemy::WallTrunEnemy(
	IWorld * world,
	const Vector2 & position,
	const Vector2& direction) :
	BaseEnemy(world, position, 64.0f, direction)
{
	//direction_ = direction;
	//BaseEnemy::Initialize();

	isUseGravity_ = false;
	isInvincible_ = true;
	// 壁捜索オブジェクトの生成
	auto wsObj = std::make_shared<FloorSearchPoint>(
		world_, position_,
		Vector2(
			(scale_ / 2.0f + 1.0f) * std::abs(direction_.x),
			(scale_ / 2.0f + 1.0f) * std::abs(direction_.y)),
		Vector2(
			scale_ * std::abs(direction_.y) + 2.0f,
			scale_ * std::abs(direction_.x) + 2.0f));
	// ワールドに追加
	world_->addActor(ActorGroup::Enemy, wsObj);
	wsObj_ = &*wsObj;
}

void WallTrunEnemy::update(float deltaTime)
{
	if (wsObj_->isGround())
		direction_ *= -1;
	wsObj_->setDirection(direction_);
	wsObj_->setPosition(position_);
}

void WallTrunEnemy::onCollide(Actor & actor)
{
	BaseEnemy::onCollide(actor);
}

void WallTrunEnemy::onMessage(EventMessage event, void *)
{
}

void WallTrunEnemy::search()
{
	// プレイヤーの捜索
	findPlayer();
	stateString_ = "捜索";
	// 捜索行動
	searchMove();
}

void WallTrunEnemy::attack()
{
}

void WallTrunEnemy::searchMove()
{
	position_ += direction_ * speed_ * deltaTimer_;
}

void WallTrunEnemy::chaseMove()
{
}
