#ifndef MINI_BOSS_MANAGER_H_
#define MINI_BOSS_MANAGER_H_

#include <list>

class MiniBoss;

class MiniBossManager {
public:
	MiniBossManager();
	void update(float deltaTime);
	// �~�j�{�X�̒ǉ����s���܂�
	void addMiniBoss(MiniBoss* miniBoss);
	// �~�j�{�X�S�̂̍�����Ԃ��������܂�
	void backToSanity();
	// �~�j�{�X�S�̂��{�X�̈ʒu�ɂ��邩��Ԃ��܂�
	bool isMiniBossAllBP();
	// �~�j�{�X���{�X�����グ��Ԃɂ��܂�
	void bossLift();
	// �����グ�I�������
	bool isLiftEnd();
	// �����グ�ړ����x�̐ݒ�
	void LiftMove(const float speed);

private:
	typedef std::list<MiniBoss*> MiniBossContainer;
	MiniBossContainer miniBosses_;
};

#endif