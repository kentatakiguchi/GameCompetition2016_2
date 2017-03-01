#ifndef STAGE3_MINI_BOSS_H_
#define STAGE3_MINI_BOSS_H_

#include "MediumBoss.h"
#include <vector>

class FloorSearchPoint;

class Stage3MiniBoss : public MediumBoss {
public:
	Stage3MiniBoss(
		IWorld* world,
		const Vector2&  position,
		const float bodyScale = 96.0f);
	void onUpdate(float deltaTime) override;

private:
	// �����ҋ@���
	void battleIdel(float deltaTime) override;
	// �ҋ@���
	void idel(float deltaTime) override;
	// �ړ����
	void move(float deltaTime) override;
	// �U�����
	void attack(float deltaTime) override;
	// ���S���
	void deadMove(float deltaTime) override;
	// �҂��s��
	void piyoriMove(float deltaTime);
	// �x�ݍs��
	void restMove(float deltaTime);
	// �v���C���[�̍U���ɓ����������̏���
	void playerAttackHit(Actor& actor) override;
	// �ǈړ��U������
	void wallAttack(float deltaTime);
	// ���V�~�j�{�X�̐������s���܂�
	void createMiniBoss(float deltaTime);

private:
	int wallCount_;					// �ǈړ��J�E���g
	float effectCreateTimer_;		// �X�^�[�G�t�F�N�g��������
	float groundTimer_;				// �ڒn����
	float mbTimer_;					// �~�j�{�X��������
	bool isEffectCreate_;			// �X�^�[�G�t�F�N�g�𐶐�������
	bool isPiyori_;					// �҂�邩
	bool isPrevWspHit_;
	Vector2 prevAttackPosition_;	// �U������O�̈ʒu
	FloorSearchPoint* wspObj_;		// �Ǒ{���I�u�W�F�N�g

	// �����R���e�i
	typedef std::vector<float> MoveDirectionContainer;
	MoveDirectionContainer moveDirections_;
	// �X�^�[�G�t�F�N�g�p�R���e�i
	typedef std::list<ActorPtr> StarContainer;
	StarContainer stars_;
};

#endif
