#ifndef WALL_ATTACK_H_
#define WALL_ATTACK_H_

#include "BossAttack.h"

class WallAttack : public BossAttack {
private:
	enum class State {
		FloorSearch,
		FloorGetOff,
		WallMove,
		WallAttack
	};

public:
	WallAttack();
	WallAttack(const Vector2& position, const float heartHp);
	// �U��
	void attack(float deltaTime) override;
	// �U���s���̃��t���b�V�����s���܂�
	virtual void Refresh() override;

private:
	// ���{����Ԃł�
	void floorSearch(float deltaTime);
	// ������~����Ԃł�
	void floorGetOff(float deltaTime);
	// �ǈړ���Ԃł�
	void wallMove(float deltaTime);
	// �ǍU����Ԃł�
	void wallAttack(float deltaTime);
	// ��Ԃ̕ύX���s���܂�
	void changeState(State state);

private:
	int hp_;		// �{�X�̗̑�(�S���̗̑�)
	State state_;	// ���
};

#endif
