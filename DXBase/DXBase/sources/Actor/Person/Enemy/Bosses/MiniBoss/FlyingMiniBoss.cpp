#include "FlyingMiniBoss.h"

FlyingMiniBoss::FlyingMiniBoss(
	IWorld * world,
	const Vector2 & position,
	const Vector2 & direction,
	const float bodyScale) :
	AdhereMiniBoss(world, position, bodyScale),
	deg_(0.0f)
{
	direction_ = direction;
}

void FlyingMiniBoss::move(float deltaTime)
{
	// �ړ�
	deg_ += 2.5f * (deltaTime * 60.0f);
	//position_.x += speed_ * timer_  * 9.8f * (deltaTime * 60.0f);
	position_.x += direction_.x * speed_ * (deltaTime * 60.0f);
	position_.y -= 2.0f * MathHelper::Sin(deg_) * (deltaTime * 60.0f);
	setTexPosition(10.0f);
	animation_.changeDirType(direction_.x);

	//deg_ += (deltaTime * 60.0f);
	//position_.x += direction_.x * 50.0f * (deltaTime * 60.0f);
	////position_.y -= 2.0f * MathHelper::Sin(deg_) * (deltaTime * 60.0f);
	//
}

// ���ɓ����������̏���
void FlyingMiniBoss::floorHit()
{
	if (isLeft_ || isRight_) {
		changeState(State::Dead, WAIT_NUMBER);
		// �ʒu�̍X�V
		//setTexPosition(-50.0f);
		// ���_�����ɂ���
		//orizin_ = Vector2::One * (256.0f / 2.0f) + Vector2::Up * 100.0f;
		// �v���C���[�Ƌt�̕���������
		//animation_.changeDirType(getPlayerDirection().x);
	}
}
