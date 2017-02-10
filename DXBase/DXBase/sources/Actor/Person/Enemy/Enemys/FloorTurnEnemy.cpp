#include "FloorTurnEnemy.h"
#include "../../../Base/ActorGroup.h"
#include "../FloorSearchPoint.h"
#include "Prickle.h"
#include "../EnemyHeaderImport.h"

#include "../Bosses/Effect/EnemyDeadEffect.h"

FloorTurnEnemy::FloorTurnEnemy(
	IWorld * world, 
	const Vector2 & position,
	float right) :
	BaseEnemy(world, position, 64.0f),
	fspObj_(nullptr)
{
	direction_ = Vector2(-right, 1.0f);
	BaseEnemy::Initialize();
	// �R�{���I�u�W�F�N�g�̒ǉ�
	auto fsObj = std::make_shared<FloorSearchPoint>(
		world_, 
		position_,
		Vector2((scale_ / 2.0f + 1.0f), scale_ / 2.0f), 
		Vector2(30.0f, 30.0f));
	world_->addActor(ActorGroup::Enemy, fsObj);
	fspObj_ = &*fsObj;
	objContainer_.push_back(fspObj_);
	// �g�Q�I�u�W�F�N�g�̐���
	auto pricleObj = std::make_shared<Prickle>(
		world_,
		position_,
		Vector2::Up * -(scale_+ 1.0f), 
		Vector2(64.0f, 64.0f));
	world_->addActor(ActorGroup::Enemy_AttackRange, pricleObj);
	pricleObj_ = &*pricleObj;
	objContainer_.push_back(pricleObj_);
}

void FloorTurnEnemy::beginUpdate(float deltaTime){}

void FloorTurnEnemy::update(float deltaTime)
{
	// ���{���I�u�W�F�N�g�������G��Ă��Ȃ��āA�ڒn���Ă���ꍇ
	// �ǐՏ�Ԃ̏ꍇ�͍s��Ȃ�
	if (!fspObj_->isGround() && isGround_ && state_ != State::Chase) {
		direction_.x *= -1;
	}
	// �R�{���I�u�W�F�N�g�̍X�V
	fspObj_->setDirection(direction_);
	fspObj_->setPosition(position_);
	// �g�Q�̍X�V
	pricleObj_->setDirection(direction_);
	pricleObj_->setEnemyPosition(position_);
}

void FloorTurnEnemy::onMessage(EventMessage event, void *){}

// �������Ă���I�u�W�F�N�g�̈ʒu��ݒ肵�܂�
void FloorTurnEnemy::setObjPosition()
{
	BaseEnemy::setObjPosition();
	fspObj_->setPosition(position_);
	pricleObj_->setEnemyPosition(position_);
}

void FloorTurnEnemy::attack(){}

void FloorTurnEnemy::searchMove()
{
	// �R�ړ�
	position_ += direction_.x * speed_ * deltaTimer_;
	pricleObj_->setAddPosition(Vector2::Up * -(scale_ + 1.0f));
}

void FloorTurnEnemy::chaseMove()
{
	// �ʏ펞�������߂ɂ���
	auto speed = speed_;
	auto distance = position_.x - enemyManager_.getPlayerPosition(discoveryNumber_).x;
	//player_->getPosition().x;
	//// �v���C���[�̎��t�߂ɗ�����~�܂�
	if (std::abs(distance) < speed) return;
	// �v���C���[�Ƃ̈ʒu�ŁA���x��␳����
	if (std::abs(distance) < speed)
		speed = std::abs(distance);
	// �ǐ�
	// �v���C���[�Ƃ�X��������̏ꍇ���������Ȃ�
	direction_.x = -enemyManager_.getPlayerDirection(discoveryNumber_).x;
	position_.x += enemyManager_.getPlayerDirection(discoveryNumber_).x *
		-speed * deltaTimer_;
	pricleObj_->setAddPosition(Vector2((scale_ + 1.0f), 0.0f));
}
