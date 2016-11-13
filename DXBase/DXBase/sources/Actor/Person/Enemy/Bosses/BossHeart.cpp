#include "BossHeart.h"

BossHeart::BossHeart(
	IWorld * world, const Vector2 & position,
	const int hp, const int bossHp) :
	Actor(world, "BossEntry", position, 
		CollisionBase(const_cast<Vector2&>(position), 10.0f)),
	hp_(hp),
	initHp_(hp_),
	bossHp_(bossHp),
	timer_(0.0f),
	isEntered_(false),
	isLetOut_(false)
{
}

void BossHeart::onUpdate(float deltaTime)
{
	isLetOut_ = false;
	// �̓��ɓ����Ă��Ȃ��Ȃ�A�Ԃ�(�������̔���)
	if (!isEntered_) return;
	timer_ += deltaTime;
	// ��莞�Ԍo�ߌ�ɖ߂�
	if (timer_ < 5.0f) return;
	// �v���C���[�̈ʒu��߂�

	// ������
	initStatus();
}

void BossHeart::onDraw() const
{
	body_.draw(inv_);

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
	// if (isLetOut_) return;
	auto actorName = actor.getName();
	if (actorName == "PlayerBody2" || actorName == "PlayerBody1") {
		hp_--;
		// �̗͂������Ȃ�����A�{�X�̗̑͂����炷
		if (hp_ <= 0) {
			bossHp_--;
			// �v���C���[���O�ɏo��

			hp_ = initHp_;
			initStatus();
		}
	}
}

void BossHeart::onMessage(EventMessage event, void *)
{
}

// �{�X�̗̑͂�Ԃ��܂�
int BossHeart::getBossHp()
{
	return bossHp_;
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
