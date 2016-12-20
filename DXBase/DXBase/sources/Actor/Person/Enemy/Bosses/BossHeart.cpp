#include "BossHeart.h"

BossHeart::BossHeart(
	IWorld * world, const Vector2 & position,
	const int hp, const int bossHp) :
	Actor(world, "BossEntry", position, 
		std::make_shared<BoundingCircle>(const_cast<Vector2&>(position),Matrix::Identity, 32.0f,true)),
	stateCount_(3),
	initStateCount_(stateCount_),
	hp_(hp * stateCount_),
	initHp_(hp_),
	prevHp_(hp_),
	bossHp_(bossHp),
	timer_(0.0f),
	isEntered_(false),
	isLetOut_(false)
{
}

void BossHeart::onUpdate(float deltaTime)
{
	// �f�o�b�O
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::N)) {
		hp_ -= 100;
		bossHp_--;
		stateCount_--;
		initStatus();
	}
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::M)) {
		hp_ -= 50;
		if (hp_ % 100 == 0) {
			bossHp_ -= 1;
		}
	}

	// �ǂ��o����false�ɂ���
	isLetOut_ = false;
	// �O��̗̑͂��X�V
	prevHp_ = hp_;
	// �̓��ɓ����Ă��Ȃ��Ȃ�A�Ԃ�(�������̔���)
	if (!isEntered_) return;
	timer_ += deltaTime;
	// �T�b�o�ߌ�ɒǂ��o�����������Ƃɂ���
	if (timer_ < 5.0f) return;
	// ������
	initStatus();
}

void BossHeart::onDraw() const
{
	body_->draw(-1,inv_);

	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	DrawString(
		vec3Pos.x, vec3Pos.y -100,
		"�S���ł�", GetColor(255, 255, 255));
	// �U���\�Ȃ�\��
	if (isEntered_) {
		// �����̕\��
		DrawString(
			vec3Pos.x, vec3Pos.y,
			"�U���\", GetColor(255, 255, 255));
		// �̗͂̕\��
		DrawFormatString(
			vec3Pos.x, vec3Pos.y - 75,
			GetColor(255, 255, 255), "�̗�:%d", hp_);
	}
}

void BossHeart::onCollide(Actor & actor)
{
	// �̓��ɓ����Ă��Ȃ��Ȃ�A�Ԃ�(�������̔���)
	if (!isEntered_) return;
	auto actorName = actor.getName();
	if (actorName == "PlayerBody2" || actorName == "PlayerBody1") {
		hp_--;
		// �����̗͂Ɖߋ��̗̑͂�����Ȃ�A�����ɕԂ�
		auto initHp = initHp_ / initStateCount_;
		if (prevHp_ == initHp * stateCount_) return;
		// �]�肪 100 �Ȃ�{�X�̗̑͂����
		// ���݂̗̗̑͂]�肪�O��̗̗̑͂]���菭�Ȃ��ꍇ
		if ((int)(hp_ / initHp) < (int)(prevHp_ / initHp)) {
			// �̗͂̕␳
			hp_ += prevHp_ - hp_;
		}
		// �̗͂���Ԃ��ς��ߖ�(100�̔{��)�Ȃ�A�{�X�̗̑͂����
		if (hp_ % initHp == 0) {
			// �̗͂������Ȃ�����A�{�X�̗̑͂����炷
			bossHp_--;
			stateCount_--;
			initStatus();
		}
	}
}

void BossHeart::onMessage(EventMessage event, void *)
{
}

// �S���̗̑͂�Ԃ��܂�
int BossHeart::getHeartHp()
{
	return hp_;
}

// �{�X�̗̑͂�Ԃ��܂�
int BossHeart::getBossHp()
{
	return bossHp_;
}

void BossHeart::addBossHp(int hp)
{
	hp_ += hp;
	if (hp_ % 100 == 0)
		bossHp_ -= 1;
}

// �v���C���[���̓��ɓ���������ݒ肵�܂�
void BossHeart::setIsEntered(bool isEntered)
{
	isEntered_ = isEntered;
}

// �v���C���[��ǂ��o��������Ԃ��܂�
bool BossHeart::isLetOut()
{
	return isLetOut_;
}

// �X�e�[�^�X�̏��������s���܂�
void BossHeart::initStatus()
{
	timer_ = 0.0f;
	isLetOut_ = true;
	isEntered_ = false;
}
