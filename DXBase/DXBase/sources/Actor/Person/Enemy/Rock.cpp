#include "Rock.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../../Define.h"
#include "../../../World/IWorld.h"
#include <random>

Rock::Rock(IWorld * world, const Vector2 & position, const float bodyScale) : 
	AdhereMiniBoss(world, position, bodyScale)
{
}

// �������
void Rock::move(float deltaTime)
{
	// ����
	position_.y += speed_ * timer_  * 9.8f * (deltaTime * 60.0f);
	setTexPosition(10.0f);
	// �v���C���[�̕���������
	animation_.changeDirType(-getPlayerDirection().x);
}

// ���S���
void Rock::deadMove(float deltaTime)
{
	AdhereMiniBoss::adhereDead(deltaTime);
}

// ���ɓ����������̏���
void Rock::floorHit()
{
	changeState(State::Dead, RUN_NUMBER);
	// �ʒu�̍X�V
	setTexPosition(-50.0f);
	// ���_�����ɂ���
	orizin_ = Vector2::One * (256.0f / 2.0f) + Vector2::Up * 100.0f;
	// �v���C���[�Ƌt�̕���������
	animation_.changeDirType(getPlayerDirection().x);
}
