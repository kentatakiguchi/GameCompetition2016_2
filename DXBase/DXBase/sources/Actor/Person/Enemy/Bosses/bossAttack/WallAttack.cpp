#include "WallAttack.h"

WallAttack::WallAttack() :
	BossAttack(Vector2::Zero),
	hp_(0),
	state_(State::FloorSearch)
{
}

WallAttack::WallAttack(const Vector2 & position, const float heartHp) :
	BossAttack(position),
	hp_(heartHp),
	state_(State::FloorSearch)
{
}

void WallAttack::attack(float deltaTime)
{
	switch (state_)
	{
	case State::FloorSearch: floorSearch(deltaTime); break;
	case State::FloorGetOff: floorGetOff(deltaTime); break;
	case State::WallMove: wallMove(deltaTime); break;
	case State::WallAttack: wallAttack(deltaTime); break;
	}
}

void WallAttack::Refresh()
{
	BossAttack::Refresh();
}

// ���{����Ԃł�
void WallAttack::floorSearch(float deltaTime)
{
	// �����Ă��鏰�ɐڒn���Ă���΁A�����~���	
	// �����łȂ���΁A�ǈړ��ɑJ��
}

// ������~����Ԃł�
void WallAttack::floorGetOff(float deltaTime)
{
	// �{�X�̈ʒu�Ə��̒��S�ʒu���Q�Ƃ��āA
	// �v�Z���ďo�Ă��������������Ĉړ�����
	// ���ʂ̏��ɐڒn������ǈړ��ɑJ��
}

// �ǈړ���Ԃł�
void WallAttack::wallMove(float deltaTime)
{
	// ���v����ňړ�
	// ��莞�Ԍo�߂ŁA�ǍU���ɑJ��
}

// �ǍU����Ԃł�
void WallAttack::wallAttack(float deltaTime)
{
	// �v���C���[�̋����ʒu�Ɍ������Ĕ��
}

// ��Ԃ̕ύX���s���܂�
void WallAttack::changeState(State state)
{
	state_ = state;
	timer_ = 0.0f;
}
