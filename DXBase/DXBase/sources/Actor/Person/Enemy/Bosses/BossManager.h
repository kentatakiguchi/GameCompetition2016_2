#ifndef BOSS_MANAGER_H_
#define BOSS_MANAGER_H_

#include "bossAttack/BossAttack.h"
#include "../../../../Math/Math.h"
#include <vector>
#include <memory>

// class BossAttack;

// �{�X�}�l�[�W���[ 
class BossManager {
public:
	BossManager();
	// �R���X�g���N�^
	BossManager(const Vector2& position);
	// �w�肵���ԍ��̍U���s�����s���܂�
	void attackMove(const float number, const float deltaTime);
	// �U���̃��t���b�V�����s���܂�
	void attackRefresh();
	// �s���ɂ���Ĉړ������ʒu��Ԃ��܂�
	Vector2 getMovePosition();
	// �U�����I����������Ԃ��܂�
	bool isAttackEnd();

public:
	// �{�X�̈ʒu��ݒ肵�܂�
	void setPosition(const Vector2& position);
	// �v���C���[�̈ʒu��ݒ肵�܂�
	void setPlayerPosition(const Vector2& position);
	// �U���O�̈ʒu�����肵�܂�
	void prevPosition();
	// �w�肵���I�u�W�F�N�g�Ƃ̕�����P�ʃx�N�g���Ŏ擾���܂�
	Vector2 getDirection(const Vector2& otherPosition);
	// �v���C���[�Ƃ̕�����P�ʃx�N�g���Ŏ擾���܂�
	Vector2 getPlayerDirection();
	// �{�X���ڒn���Ă��邩��ݒ肵�܂�
	void setIsGround(bool isGround);
	// �{�X���ǂ̉����ɓ�����������ݒ肵�܂�
	void setIsBottom(bool isBottom);

private:
	int attackNumber_;			// �U���ԍ�
	Vector2 bossPosition_;		// �{�X�̈ʒu
	Vector2 playerPosition_;	// �v���C���[�̈ʒu
	//float timer_;			// ����
	//bool isAttackEnd_;		// �U�����I�����Ă��邩

	// �{�X�U���R���e�i
	typedef std::vector<std::shared_ptr<BossAttack>> BossAttackContainer;
	BossAttackContainer bossAttackContainer_;
};

#endif
