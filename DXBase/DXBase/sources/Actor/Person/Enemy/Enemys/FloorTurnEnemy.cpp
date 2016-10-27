#include "FloorTurnEnemy.h"
#include "../../../Base/ActorGroup.h"
#include "../FloorSearchPoint.h"

FloorTurnEnemy::FloorTurnEnemy(IWorld * world, const Vector3 & position) :
	BaseEnemy(world, position, 64.0f),
	fspObj_(nullptr)
{
	// �R�{���I�u�W�F�N�g�̒ǉ�
	auto fsObj = std::make_shared<FloorSearchPoint>(
		world_, Vector3(
			-(scale_ / 2.0f + 1.0f), scale_ / 2.0f + 1.0f, 0.0f), position_);
	// ���[���h�ɒǉ�
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
	// �R�{���I�u�W�F�N�g�̍X�V
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
	// �R�ړ�(��)
	//position_ += enemyManager_.cliffMove(true) * speed_;
}

void FloorTurnEnemy::chaseMove()
{
	// �ʏ펞�������߂ɂ���
	auto speed = speed_ + 1.5f;
	auto distance = position_.x - player_->getPosition().x;
	//// �v���C���[�̎��t�߂ɗ�����~�܂�
	//if (std::abs(distance) < speed) return;
	// �v���C���[�Ƃ̈ʒu�ŁA���x��␳����
	if (std::abs(distance) < speed)
		speed = std::abs(distance);
	// �ǐ�
	position_ += enemyManager_.getPlayerDirection().x * -speed;
}
