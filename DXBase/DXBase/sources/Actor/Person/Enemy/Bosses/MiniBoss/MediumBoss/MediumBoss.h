#ifndef MEDIUM_BOSS_H_
#define MEDIUM_BOSS_H_

#include "../FighterMiniBossh.h"
#include <random>

class BossGaugeUI;

class MediumBoss : public FighterMiniBoss {
public:
	MediumBoss(
		IWorld* world,
		const Vector2&  position,
		const float bodyScale = 64.0f);
	virtual void onUpdate(float deltaTime) override;
	void onDraw()const override;

protected:
	// �����ҋ@���
	virtual void battleIdel(float deltaTime) override;
	// �ҋ@���
	virtual void idel(float deltaTime) override;
	// �ړ����
	virtual void move(float deltaTime) override;
	// �U�����
	virtual void attack(float deltaTime) override;
	// ���S���
	virtual void deadMove(float deltaTime) override;
	// ���ɓ����������̏���
	virtual void floorHit() override;
	// �v���C���[�̍U���ɓ����������̏���
	virtual void playerAttackHit(Actor & actor) override;
	// �����_���̒l���擾���܂�
	int getRandomInt(const int min, const int max);

protected:
	int hp_;					// �̗�
	int damage_;				// �_���[�W��
	Vector2 direction_;			// ����
	BossGaugeUI* bossGaugeUI_;	// �Q�[�WUI

private:
	std::mt19937 mt_;			// �����̏���seed
};

#endif