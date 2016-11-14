#include "FloorTurnEnemy.h"
#include "../../../Base/ActorGroup.h"
#include "../FloorSearchPoint.h"
#include "Prickle.h"

FloorTurnEnemy::FloorTurnEnemy(IWorld * world, const Vector2 & position) :
	BaseEnemy(world, position, 64.0f),
	fspObj_(nullptr)
{
	BaseEnemy::Initialize();

	// 崖捜索オブジェクトの追加
	auto fsObj = std::make_shared<FloorSearchPoint>(
		world_, 
		position_,
		Vector2(-(scale_ / 2.0f + 1.0f), scale_ / 2.0f), 
		Vector2(16.0f, 16.0f));
	/*auto fsObj = std::make_shared<FloorSearchPoint>(
		world_,
		position_,
		Vector2(-(scale_ / 2.0f + 1.0f), scale_ / 2.0f + 3.0f),
		2.0f);*/
	// ワールドに追加
	world_->addActor(ActorGroup::Enemy, fsObj);
	fspObj_ = &*fsObj;

	// トゲオブジェクトの生成
	auto pricleObj = std::make_shared<Prickle>(
		world_,
		Vector2::Zero,
		Vector2::Up * -(scale_+ 1.0f), 
		Vector2(64.0f, 64.0f));
	world_->addActor(ActorGroup::Enemy_AttackRange, pricleObj);
	pricleObj_ = &*pricleObj;
}

void FloorTurnEnemy::onUpdate(float deltaTime)
{
	// 崖捜索オブジェクトの更新
	//fspObj_->setDirection(direction_);
	//fspObj_->setPosition(position_);

	BaseEnemy::onUpdate(deltaTime);
	// if (!fspObj_->isGround() && fspScript->isGround())

	if (!fspObj_->isGround() && isGround_) {
		direction_.x *= -1;
	}
	// 崖捜索オブジェクトの更新
	fspObj_->setDirection(direction_);
	fspObj_->setPosition(position_);
	// トゲの更新
	pricleObj_->setDirection(direction_);
	pricleObj_->setEnemyPosition(position_);
}

void FloorTurnEnemy::onCollide(Actor & actor)
{
	BaseEnemy::onCollide(actor);
}

void FloorTurnEnemy::onMessage(EventMessage event, void *)
{
}

void FloorTurnEnemy::idel()
{
}

void FloorTurnEnemy::attack()
{
}

void FloorTurnEnemy::searchMove()
{
	speed_ = initSpeed_;
	position_ +=
		enemyManager_.cliffMove(false)
		* speed_ * deltaTimer_ *direction_.x;
	pricleObj_->setAddPosition(Vector2::Up * -(scale_ + 1.0f));
	// 崖移動(仮)
	//position_ += enemyManager_.cliffMove(true) * speed_;
}

void FloorTurnEnemy::chaseMove()
{
	// 通常時よりも速めにする
	auto speed = speed_;
	auto distance = position_.x - player_->getPosition().x;
	//// プレイヤーの軸付近に来たら止まる
	//if (std::abs(distance) < speed) return;
	// プレイヤーとの位置で、速度を補正する
	if (std::abs(distance) < speed)
		speed = std::abs(distance);
	// 追跡
	position_ += enemyManager_.getPlayerDirection().x * -speed * deltaTimer_;
	pricleObj_->setAddPosition(Vector2::Right * -(scale_ + 1.0f));
}
