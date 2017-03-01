#include "Rock.h"
#include "Bosses/MiniBoss/ImportAnimationNumber.h"
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
	position_.y += speed_ * stateTimer_  * 9.8f * (deltaTime * 60.0f);
	addTexPos_ = Vector2::Up * 10.0f;
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
	if (state_ == State::Attack || state_ == State::Dead) return;
	changeState(State::Dead, RUN_NUMBER);
	// �ʒu�̍X�V
	addTexPos_ = Vector2::Up * -50.0f;
	// ���_�����ɂ���
	orizin_ = Vector2::One * (256.0f / 2.0f) + Vector2::Up * 100.0f;
	// �v���C���[�Ƌt�̕���������
	animation_.changeDirType(getPlayerDirection().x);
}
