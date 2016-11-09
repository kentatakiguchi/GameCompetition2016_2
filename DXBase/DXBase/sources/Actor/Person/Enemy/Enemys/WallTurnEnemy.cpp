#include "WallTurnEnemy.h"
#include "../../../Base/ActorGroup.h"
#include "../FloorSearchPoint.h"
#include "Prickle.h"

WallTrunEnemy::WallTrunEnemy(IWorld * world, const Vector2 & position) :
	BaseEnemy(world, position, 64.0f)
{
	BaseEnemy::Initialize();

	isUseGravity_ = false;
	isInvincible_ = true;
	// 壁捜索オブジェクトの生成
	auto wsObj = std::make_shared<FloorSearchPoint>(
		world_, position_,
		Vector2(0.0f, -(scale_ / 2.0f + 1.0f)),
		Vector2(scale_, 2.0f));
	// ワールドに追加
	world_->addActor(ActorGroup::Enemy, wsObj);
	wsObj_ = &*wsObj;

	// トゲオブジェクトの生成(for文で回す)
	/*auto pricklePos = Vector2(64.0f, 64.0f);
	for (int i = 0; i != 8; ++i) {
		auto degree = i * 45.0f;
		auto px = pricklePos.x *  MathHelper::Cos(degree);
		auto py = pricklePos.y * MathHelper::Sin(degree);
		auto pricleObj = std::make_shared<Prickle>(
			world_, position_, Vector2(px, py), Vector2(10.0f, 10.0f));
		world_->addActor(ActorGroup::Enemy_AttackRange, pricleObj);
	}*/

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

void WallTrunEnemy::attack()
{
}

void WallTrunEnemy::searchMove()
{
	position_ += Vector2::Down * speed_ * direction_.y * deltaTimer_;
}

void WallTrunEnemy::chaseMove()
{
}
