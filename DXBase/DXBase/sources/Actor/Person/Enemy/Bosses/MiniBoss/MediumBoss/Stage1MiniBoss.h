#ifndef STAGE1_MINI_BOSS_H_
#define STAGE1_MINI_BOSS_H_

#include "MediumBoss.h"
#include <map>

class Stage1MiniBoss : public MediumBoss {
public:
	Stage1MiniBoss(
		IWorld* world,
		const Vector2& position,
		const float bodyScale = 96.0f);

private:
	// �ҋ@���
	void idel(float deltaTime) override;
	// �ړ����
	void move(float deltaTime) override;
	// �U�����
	void attack(float deltaTime) override;
	// �H�U��
	void wingAttack();

private:
	int attackCount_;			// �U����
	bool isAttack_;				// �U��������
	Vector2 direction_;			// ����
	// �H�̉�]�R���e�i
	typedef std::map<int, float> WingDegreeMap;
	WingDegreeMap wingDegrees;
};

#endif
