#ifndef BOSS_MANAGER_H_
#define BOSS_MANAGER_H_

#include "bossAttack/BossAttack.h"
#include "../../../../Math/Math.h"
#include <vector>
#include <memory>

// class BossAttack;

class BossManager {
public:
	BossManager();
	// �R���X�g���N�^
	BossManager(const Vector2& position);
	// �w�肵���ԍ��̍U���s�����s���܂�
	void attackMove(const float number, const float deltaTime);
	// �s���̃��t���b�V�����s���܂�
	void moveRefresh();
	// �s���ɂ���Ĉړ������ʒu��Ԃ��܂�
	Vector2 getMovePosition();
	// �U�����I����������Ԃ��܂�
	bool isAttackEnd();

public:
	// �w�肵���I�u�W�F�N�g�Ƃ̕�����P�ʃx�N�g���Ŏ擾���܂�
	Vector2 getDirection(const Vector2& otherPosition);
	// �v���C���[�Ƃ̕�����P�ʃx�N�g���Ŏ擾���܂�
	Vector2 getPlayerDirection();

private:
	int attackNumber_;		// �U���ԍ�
	//float timer_;			// ����
	//bool isAttackEnd_;		// �U�����I�����Ă��邩

	// �{�X�U���R���e�i
	typedef std::vector<std::shared_ptr<BossAttack>> BossAttackContainer;
	BossAttackContainer bossAttackContainer_;
};

#endif
