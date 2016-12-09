#include "FlyingEnemy.h"
#include "../../../Base/ActorGroup.h"
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
	pastPosition(Vector2::Zero),
	wsObj_(nullptr)
{
	direction_ = Vector2(1.0f, Down);
	BaseEnemy::Initialize();

	isUseGravity_ = false;
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
	addAnimation();
	animation_.changeAnimation(ENEMY_WALK);
}

void FlyingEnemy::beginUpdate(float deltaTime)
{
	// �g�Q�̍X�V
	//pricleObj_->setDirection(direction_);
	pricleObj_->setEnemyPosition(position_);
}

void FlyingEnemy::update(float deltaTime)
{
	wsObj_->setDirection(direction_);
	wsObj_->setPosition(position_);
}

//void FlyingEnemy::onDraw() const
//{
//	auto stateChar = stateString_.c_str();
//	// �G�̕\��
//	DrawGraph(
//		position_.x - scale_ / 2.0f, position_.y - scale_ / 2.0f,
//		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_SAMPLE_TEX), 0);
//	// �����̕\��
//	DrawString(
//		position_.x - scale_, position_.y - 20 - scale_,
//		stateChar, GetColor(255, 255, 255));
//
//	// �f�o�b�O
//	DrawFormatString(
//		25, 75, GetColor(255, 255, 255), 
//		"�v���C���[�Ƃ�X����:%d", (int)(position_ - pastPosition).x);
//}

void FlyingEnemy::onCollide(Actor & actor)
{
	BaseEnemy::onCollide(actor);
}

void FlyingEnemy::onMessage(EventMessage event, void *)
{
}

// ���G�ړ��ł�
void FlyingEnemy::search()
{
	// �v���C���[�̑{��
	findPlayer();
	stateString_ = "�{��";
	// �������x�ɖ߂�
	speed_ = initSpeed_;
	// �{���s��
	searchMove();
	// �v���C���[�����݂��Ȃ���΁A�{���Ƒҋ@��ԈȊO�͍s��Ȃ�
	if (!isPlayer_) return;
	// ��苗�����ŁA�v���C���[�Ƃ̊ԂɃu���b�N���Ȃ�������
	// �ǐՂ���
	if (enemyManager_.getPlayerLength() <= discoveryLenght_ &&
		psObj_->isPlayerLook()) {
		changeState(State::Chase, ENEMY_ATTACK);
		discoveryPosition_ = position_;
		// �ߋ��̈ʒu������
		auto player = world_->findActor("PlayerBody1");
		pastPosition = player->getPosition();
		pricleObj_->setDirection(enemyManager_.getDirection(pastPosition));
		// ��]
		if (enemyManager_.getDirection(pastPosition).x < 0)
			TexDegress_ = 90;
		else TexDegress_ = 270;
	}
}

void FlyingEnemy::discovery()
{
	/*auto player = world_->findActor("PlayerBody1");
	pastPosition = player->getPosition();
	pricleObj_->setDirection(enemyManager_.getDirection(pastPosition));
	changeState(State::Chase, ENEMY_WALK);*/
}

void FlyingEnemy::attack()
{
}

void FlyingEnemy::searchMove()
{
	// ���x / �`�b�v�T�C�Y�̑傫��
	// => direTimer_ = 1 => �}�b�v�`�b�v������������Ƃɂ���	
	direTimer_ += (speed_ / CHIPSIZE) * deltaTimer_;
	// ���ɓ����邩�A���̃}�b�v�`�b�v����������A�����]��
	// (wsObj_->isGround() || direTimer_ >= 14.0f)
	if (wsObj_->isGround() || direTimer_ >= 3.0f) {
		direction_.y *= -1;
		direTimer_ = 0;
	}
	position_ += Vector2::Down * speed_ * direction_.y * deltaTimer_;
	pricleObj_->setDirection(Vector2::Up);
	pricleObj_->setAddPosition(Vector2::Up * -(scale_ + 1.0f));
	//pDirection_ = enemyManager_.getPlayerNormalizeDirection();
}

// �v���C���[�̒ǐՍs���ł�
void FlyingEnemy::chase()
{
	// �v���C���[�̑{��
	findPlayer();
	stateString_ = "�ǐ�";
	// �ړ����x��{���ɂ���
	speed_ = initSpeed_ * 1.5f;
	// �ǐՍs��
	chaseMove();
}

void FlyingEnemy::chaseMove()
{
	// �v���C���[�̂��������ɐi��
	// �v���C���[�������ʒu�Ƃ̋������O�Ȃ�΁A������
	// pastPosition -= world_->MoveActor();
	auto direction = enemyManager_.getDirection(pastPosition);
	auto p_Direction = position_ - pastPosition;
 	auto length = p_Direction.Length();
	/*pricleObj_->setDirection(-direction);
	pricleObj_->setAddPosition(Vector2::Left * (scale_ + 1.0f));*/
	// �v���C���[�����ɂ���ꍇ�A���̋������ɋ��邱�Ƃ�����̂ŁA�؂�グ��
	if (length <= 15) {
		//changeState(State::Lost, ENEMY_LOST);
		changeState(State::Lost, ENEMY_WALK);
		return;
	}
	// �ڒn���Ă�����Ay�x�N�g���� 0 �ɂ���
	if (wsObj_->isGround() || isGround_)
		p_Direction.y = 0;
	auto speed = speed_;
	if (length < speed_)
		speed = length;
	// �v���C���[�̋����ʒu����̕�����ݒ�
	direction_ = enemyManager_.getDirection(pastPosition);
	// �v���C���[�̋����ʒu�ɐi��
	direction.y *= -1;
	position_ += -direction.Normalize() * speed * deltaTimer_;
	// �g�Q�̐ݒ�
	//pricleObj_->setDirection(direction);
	pricleObj_->setAddPosition(Vector2::Left * (scale_ + 1.0f));
}

// �G�������������̍s���ł�
void FlyingEnemy::lostMove()
{
	// ������
	stateString_ = "������";
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
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_FLYINGENEMY_WALK_TEX),
		texSize_, 8, 3, 3);
	animation_.addAnimation(
		ENEMY_ATTACK,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_FLYINGENEMY_ATTACK_TEX),
		texSize_, 8, 2, 5);
	animation_.addAnimation(
		ENEMY_DAMAGE,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_FLYINGENEMY_DAMAGE_TEX),
		texSize_, 8, 3, 3);
}
