#ifndef WING_ATTACK_MINI_BOSS_H_
#define WING_ATTACK_MINI_BOSS_H_

#include "FighterMiniBossh.h"
#include <map>
#include <random>

class WingAttackMiniBoss : public FighterMiniBoss {
public:
	WingAttackMiniBoss(
		IWorld* world,
		const Vector2&  position,
		const float bodyScale = 64.0f);
	/*void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;*/

private:
	// �ҋ@���
	void idel(float deltaTime) override;
	// �ړ����
	void move(float deltaTime) override;
	//  
	void attack(float deltaTime) override;
	// ���S���
	void deadMove(float deltaTime) override;
	// �A�j���[�V�����̒ǉ�
	void addAnimation() override;
	// �H�U��
	void wingAttack();

private:
	int attackCount_;			// �U����
	bool isAttack_;				// �U��������
	Vector2 direction_;			// ����
	std::mt19937 mt_;			// �����̏���seed
	// �H�̉�]�R���e�i
	typedef std::map<int, float> WingDegreeMap;
	WingDegreeMap wingDegrees;
};

#endif