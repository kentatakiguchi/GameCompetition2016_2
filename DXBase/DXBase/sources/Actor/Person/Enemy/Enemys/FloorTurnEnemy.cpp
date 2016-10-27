#include "FloorTurnEnemy.h"
#include "../../../Base/ActorGroup.h"
#include "../FloorSearchPoint.h"

FloorTurnEnemy::FloorTurnEnemy(IWorld * world, const Vector3 & position) :
	BaseEnemy(world, position, 64.0f),
	fspObj_(nullptr)
{
	// 崖捜索オブジェクトの追加
	auto fsObj = std::make_shared<FloorSearchPoint>(
		world_, Vector3(
			-(scale_ / 2.0f + 1.0f), scale_ / 2.0f + 1.0f, 0.0f), position_);
	// ワールドに追加
	world_->addActor(ActorGroup::Enemy, fsObj);
	fspObj_ = &*fsObj;
}

void FloorTurnEnemy::onUpdate(float deltaTime)
{
	BaseEnemy::onUpdate(deltaTime);
	if (!fspObj_->isGround() && fsPointScript->isGround()) {
		directionX_ *= -1;
	}
	fspObj_->setDirectionX(directionX_);
	// 崖捜索オブジェクトの更新
	fspObj_->setPosition(position_);
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

void FloorTurnEnemy::Attack()
{
}

void FloorTurnEnemy::searchMove()
{
	speed_ = initSpeed_;
	position_ += 
		enemyManager_.cliffMove(fsPointScript->isFloor())
		* speed_ * directionX_;
	// 崖移動(仮)
	//position_ += enemyManager_.cliffMove(true) * speed_;
}

void FloorTurnEnemy::chaseMove()
{
	// 通常時よりも速めにする
	auto speed = speed_ + 1.5f;
	auto distance = position_.x - player_->getPosition().x;
	//// プレイヤーの軸付近に来たら止まる
	//if (std::abs(distance) < speed) return;
	// プレイヤーとの位置で、速度を補正する
	if (std::abs(distance) < speed)
		speed = std::abs(distance);
	// 追跡
	position_ += enemyManager_.getPlayerDirection().x * -speed;
}
