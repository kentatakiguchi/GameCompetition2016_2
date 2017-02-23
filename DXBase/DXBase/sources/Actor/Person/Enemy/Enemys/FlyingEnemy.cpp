#include "FlyingEnemy.h"
#include "../../../Base/ActorGroup.h"
#include "../EnemyHeaderImport.h"
#include "../FloorSearchPoint.h"
#include "Prickle.h"
#include "../PlayerSearchObj.h"

FlyingEnemy::FlyingEnemy(
	IWorld * world,
	const Vector2 & position, 
	float Down) :
	BaseEnemy(world, position, 64.0f),
	direTimer_(0.0f),
	lostTimer_(0.0f),
	pastPosition_(Vector2::Zero),
	wsObj_(nullptr)
{
	direction_ = Vector2(1.0f, Down);
	BaseEnemy::Initialize();

	isUseGravity_ = false;
	deadAnimaID_ = AnimationID::ENEMY_FLYINGENEMY_DAMAGE_TEX;
	// �Ǒ{���I�u�W�F�N�g�̐���
	auto wsObj = std::make_shared<FloorSearchPoint>(
		world_, position_,
		Vector2(0.0f, -(scale_ / 2.0f + 1.0f)), 
		Vector2(scale_, 2.0f));
	// ���[���h�ɒǉ�
	world_->addActor(ActorGroup::Enemy, wsObj);
	wsObj_ = &*wsObj;
	objContainer_.push_back(wsObj_);
	// �g�Q�I�u�W�F�N�g�̐���
	auto pricleObj = std::make_shared<Prickle>(
		world_,
		Vector2::Zero,
		Vector2::Up * -(scale_ + 1.0f),
		Vector2(64.0f, 64.0f));
	world_->addActor(ActorGroup::Enemy_AttackRange, pricleObj);
	pricleObj_ = &*pricleObj;
	objContainer_.push_back(pricleObj_);
	pricleObj_->setDirection(direction_);
	// �A�j���[�V�����̒ǉ�
	addTexPosition_ = Vector2::Zero;
}

void FlyingEnemy::beginUpdate(float deltaTime)
{
	// �g�Q�̍X�V
	pricleObj_->setEnemyPosition(position_);
}

void FlyingEnemy::update(float deltaTime)
{
	wsObj_->setDirection(direction_);
	wsObj_->setPosition(position_);
}

void FlyingEnemy::onMessage(EventMessage event, void *){}

// ���G�ړ��ł�
void FlyingEnemy::search()
{
	// �v���C���[�̑{��
	findPlayer();
	// �������x�ɖ߂�
	speed_ = initSpeed_;
	// �{���s��
	searchMove();
	// �v���C���[�����݂��Ȃ���΁A�{���Ƒҋ@��ԈȊO�͍s��Ȃ�
	if (!isPlayer_) return;
	// ��苗�����ŁA�v���C���[�Ƃ̊ԂɃu���b�N���Ȃ�������
	// �ǐՂ���
	for (int i = 0; i != 1; i++) {
		auto a = enemyManager_.getPlayerNormalizeDirection(i);
		auto b = Vector2::Right * direction_;
		auto radius = std::atan2f(b.x * a.y - a.x * b.y, a.x * b.x + a.y * b.y);
		auto deg = MathHelper::ToDegrees(radius);
		// �ǐՂ���
		// psObj_->isPlayerLook()
		if (enemyManager_.getPlayerLength(i) <= discoveryLenght_ &&
			std::abs(deg) <= 30.0f &&
			enemyManager_.getPSObj(i)->isPlayerLook()) {
			changeState(State::Chase, ENEMY_ATTACK);
			discoveryPosition_ = position_;
			// �ߋ��̈ʒu������
			auto player = world_->findActor("PlayerBody1");
			pastPosition_ = player->getPosition();
			pricleObj_->setDirection(enemyManager_.getDirection(pastPosition_));
			// ��]
			if (enemyManager_.getDirection(pastPosition_).x < 0)
				texDegress_ = 90;
			else texDegress_ = 270;
			break;
		}
	}
	/*if (enemyManager_.getPlayerLength() <= discoveryLenght_ &&
		psObj_->isPlayerLook()) {
		
	}*/
}

void FlyingEnemy::discovery(){}

void FlyingEnemy::attack(){}

void FlyingEnemy::searchMove()
{
	// ���x / �`�b�v�T�C�Y�̑傫��
	// => direTimer_ = 1 => �}�b�v�`�b�v������������Ƃɂ���	
	direTimer_ += (speed_ / CHIPSIZE) * deltaTimer_;
	// ���ɓ����邩�A���̃}�b�v�`�b�v����������A�����]��
	if (wsObj_->isGround() || direTimer_ >= 3.0f) {
		direction_.y *= -1;
		direTimer_ = 0;
	}
	position_ += Vector2::Down * speed_ * direction_.y * deltaTimer_;
	pricleObj_->setDirection(Vector2::Up);
	pricleObj_->setAddPosition(Vector2::Up * -(scale_ + 1.0f));
}

// �v���C���[�̒ǐՍs���ł�
void FlyingEnemy::chase()
{
	// �v���C���[�̑{��
	findPlayer();
	// �ړ����x��{���ɂ���
	speed_ = initSpeed_ * 1.5f;
	// �ǐՍs��
	chaseMove();
}

void FlyingEnemy::chaseMove()
{
	// �v���C���[�̂��������ɐi��
	// �v���C���[�������ʒu�Ƃ̋������O�Ȃ�΁A������
	auto direction = enemyManager_.getDirection(pastPosition_);
	auto p_Direction = position_ - pastPosition_;
 	auto length = p_Direction.Length();
	// �v���C���[�����ɂ���ꍇ�A���̋������ɋ��邱�Ƃ�����̂ŁA�؂�グ��
	if (length <= 15) {
		//changeState(State::Lost, ENEMY_LOST);
		changeState(State::Lost, ENEMY_WALK);
		texDegress_ = 0.0f;
		return;
	}
	// �ڒn���Ă�����Ay�x�N�g���� 0 �ɂ���
	if (wsObj_->isGround() || isGround_)
		p_Direction.y = 0;
	auto speed = speed_;
	if (length < speed_)
		speed = length;
	// �v���C���[�̋����ʒu����̕�����ݒ�
	direction_ = enemyManager_.getNormalizeDirection(pastPosition_);
	// �v���C���[�̋����ʒu�ɐi��
	position_ += direction_ * speed * deltaTimer_;
	// �g�Q�̐ݒ�
	pricleObj_->setAddPosition(Vector2::Left * (scale_ + 1.0f));
}

// �G�������������̍s���ł�
void FlyingEnemy::lostMove()
{
	// ������
	lostTimer_ += deltaTimer_ / 60.0f;
	if (lostTimer_ <= 8.0f) return;
	lostTimer_ = 0.0f;
	changeState(State::Search, ENEMY_WALK);
}

// �A�j���[�V�����̒ǉ����s���܂�
void FlyingEnemy::addAnimation()
{
	animation_.addAnimation(
		ENEMY_WALK,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::ENEMY_FLYINGENEMY_WALK_TEX));
	animation_.addAnimation(
		ENEMY_ATTACK,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::ENEMY_FLYINGENEMY_ATTACK_TEX));
	animation_.addAnimation(
		ENEMY_DAMAGE,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::ENEMY_FLYINGENEMY_DAMAGE_TEX));
}
