#include "WallTurnEnemy.h"
#include "../../../Base/ActorGroup.h"
#include "../FloorSearchPoint.h"
#include "Prickle.h"

WallTrunEnemy::WallTrunEnemy(IWorld * world, const Vector2 & position) :
	BaseEnemy(world, position, 64.0f)
{
	isUseGravity_ = false;
	isInvincible_ = true;
	// 壁捜索オブジェクトの生成
	auto wsObj = std::make_shared<FloorSearchPoint>(
		world_, Vector2(0.0f, -(scale_ / 2.0f + 1.0f)), position_);
	// ワールドに追加
	world_->addActor(ActorGroup::Enemy, wsObj);
	wsObj_ = &*wsObj;

	//// トゲオブジェクトの生成(for文で回す)
	//auto pricleObj = std::make_shared<Prickle>(
	//	world_, position_, Vector3::Zero, 32.0f);
	//world_->addActor(ActorGroup::Enemy_AttackRange, pricleObj);
	//pricleObj_ = &*pricleObj;
}

void WallTrunEnemy::onUpdate(float deltaTime)
{
	BaseEnemy::onUpdate(deltaTime);
	if (wsObj_->isGround())
		direction_.y *= -1;
	wsObj_->setDirection(direction_);
	wsObj_->setPosition(position_);

	/*pricleObj_->setDirection(direction_);
	pricleObj_->setEnemyPosition(position_);*/
}

void WallTrunEnemy::onCollide(Actor & actor)
{
	BaseEnemy::onCollide(actor);
}

void WallTrunEnemy::onMessage(EventMessage event, void *)
{
}

void WallTrunEnemy::idel()
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

void WallTrunEnemy::Attack()
{
}

void WallTrunEnemy::searchMove()
{
	position_ += Vector2::Down * speed_ * direction_.y * deltaTimer_;
}

void WallTrunEnemy::chaseMove()
{
}
