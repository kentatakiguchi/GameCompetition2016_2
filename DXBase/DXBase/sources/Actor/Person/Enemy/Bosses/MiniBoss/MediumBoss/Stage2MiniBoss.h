#ifndef STAGE2_MINI_BOSS_H_
#define STAGE2_MINI_BOSS_H_

#include "MediumBoss.h"
#include <vector>

class Stage2MiniBoss : public MediumBoss{
public:
	Stage2MiniBoss(
		IWorld* world,
		const Vector2&  position,
		const float bodyScale = 96.0f);

private:
	// �ҋ@���
	void idel(float deltaTime) override;
	// �ړ����
	void move(float deltaTime) override;
	// �U�����
	void attack(float deltaTime) override;
	// ���S���
	void deadMove(float deltaTime) override;
	// ���ɓ����������̏���
	void floorHit() override;
	// �҂��s��
	void piyoriMove(float deltaTime);
	// �߂�s��
	void returnMove(float deltaTime);

private:
	float movePositionCount_;		// �ړ��������v��
	float effectCreateTimer_;		// �X�^�[�G�t�F�N�g��������
	bool isEffectCreate_;			// �X�^�[�G�t�F�N�g�𐶐�������
	bool isReturn_;					// �w��̈ʒu�ɖ߂邩
	Vector2 prevAttackPosition_;	// �U������O�̈ʒu
	// �X�^�[�G�t�F�N�g�p�R���e�i
	typedef std::list<ActorPtr> StarContainer;
	StarContainer stars_;
		//stars_
	//Vector2 prevPlayerDirection_;	// �O��̃v���C���[�Ƃ̕���
};

#endif
