#include "WallTurnEnemy.h"
#include "../../../Base/ActorGroup.h"
#include "../FloorSearchPoint.h"

WallTrunEnemy::WallTrunEnemy(IWorld * world, const Vector3 & position) :
	BaseEnemy(world, position, 64.0f)
{
	isUseGravity_ = false;
	isInvincible_ = true;
	// �R�{���I�u�W�F�N�g�̒ǉ�
	auto wsObj = std::make_shared<FloorSearchPoint>(
		world_, Vector3(0.0f, -(scale_ / 2.0f + 1.0f), 0.0f), position_);
	// ���[���h�ɒǉ�
	world_->addActor(ActorGroup::Enemy, wsObj);
	wsObj_ = &*wsObj;
}

void WallTrunEnemy::onUpdate(float deltaTime)
{
	BaseEnemy::onUpdate(deltaTime);
	if (wsObj_->isGround())
		directionY_ *= -1;
	wsObj_->setDirectionY(directionY_);
	wsObj_->setPosition(position_);
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
	// �v���C���[�̑{��
	findPlayer();
	color_ = GetColor(0, 255, 0);
	stateString_ = "�{��";
	// �{���s��
	searchMove();
}

void WallTrunEnemy::Attack()
{
}

void WallTrunEnemy::searchMove()
{
	position_ += Vector3::Down * speed_ * directionY_;
}

void WallTrunEnemy::chaseMove()
{
}
