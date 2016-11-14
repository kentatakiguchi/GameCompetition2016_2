#include "FloorTurnEnemy.h"
#include "../../../Base/ActorGroup.h"
#include "../FloorSearchPoint.h"
#include "Prickle.h"

FloorTurnEnemy::FloorTurnEnemy(IWorld * world, const Vector2 & position) :
	BaseEnemy(world, position, 64.0f),
	fspObj_(nullptr)
{
	BaseEnemy::Initialize();

	// �R�{���I�u�W�F�N�g�̒ǉ�
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
	// ���[���h�ɒǉ�
	world_->addActor(ActorGroup::Enemy, fsObj);
	fspObj_ = &*fsObj;

	// �g�Q�I�u�W�F�N�g�̐���
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
	// �R�{���I�u�W�F�N�g�̍X�V
	//fspObj_->setDirection(direction_);
	//fspObj_->setPosition(position_);

	BaseEnemy::onUpdate(deltaTime);
	// if (!fspObj_->isGround() && fspScript->isGround())

	if (!fspObj_->isGround() && isGround_) {
		direction_.x *= -1;
	}
	// �R�{���I�u�W�F�N�g�̍X�V
	fspObj_->setDirection(direction_);
	fspObj_->setPosition(position_);
	// �g�Q�̍X�V
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
	// �R�ړ�(��)
	//position_ += enemyManager_.cliffMove(true) * speed_;
}

void FloorTurnEnemy::chaseMove()
{
	// �ʏ펞�������߂ɂ���
	auto speed = speed_;
	auto distance = position_.x - player_->getPosition().x;
	//// �v���C���[�̎��t�߂ɗ�����~�܂�
	//if (std::abs(distance) < speed) return;
	// �v���C���[�Ƃ̈ʒu�ŁA���x��␳����
	if (std::abs(distance) < speed)
		speed = std::abs(distance);
	// �ǐ�
	position_ += enemyManager_.getPlayerDirection().x * -speed * deltaTimer_;
	pricleObj_->setAddPosition(Vector2::Right * -(scale_ + 1.0f));
}
