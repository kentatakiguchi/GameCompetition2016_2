#ifndef PLURAL_WALL_ATTACK_H_
#define PLURAL_WALL_ATTACK_H_

#include "WallAttack.h"

class PluralWallAttack : public WallAttack {
public:
	PluralWallAttack();
	PluralWallAttack(const Vector2& position);
	// �U��
	void attack(float deltaTime) override;
	// �U���s���̃��t���b�V�����s���܂�
	void Refresh() override;

private:
	int aCount_;			// �U����
	int initACount_;		// �����̍U����
	float idelTimer_;
	//int flinck
};

#endif