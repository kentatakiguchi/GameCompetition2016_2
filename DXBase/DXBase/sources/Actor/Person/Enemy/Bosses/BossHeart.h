#ifndef BOSS_HEART_H_
#define BOSS_HEART_H_

#include "../../../Base/Actor.h"
#include "../../../../Animation/Animation2D.h"
#include "../../../../World/IWorld.h"
#include "../../../../Math/Math.h"
#include "../../../../Define.h"

// �{�X�S���N���X
class BossHeart : public Actor {
public:
	BossHeart(IWorld* world, const Vector2&  position, const int hp, const int bossHp);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

public:
	// �S���̗̑͂�Ԃ��܂�
	int getHeartHp();
	// �{�X�̗̑͂�Ԃ��܂�
	int getBossHp();
	// �v���C���[���̓��ɓ���������ݒ肵�܂�
	void setIsEntered(bool isEntered);
	// �v���C���[��ǂ��o��������Ԃ��܂�
	bool isLetOut();

private:
	// �X�e�[�^�X�̏��������s���܂�
	void initStatus();

private:
	int stateCount_;		// ��Ԃ̌�
	int initStateCount_;	// ��Ԃ̌�(�����l)
	int hp_;				// �̗�
	int initHp_;			// �̗�(�����l)
	int prevHp_;			// �̗�(�O��̗̑�)
	int bossHp_;			// �{�X�̗̑�
	float timer_;			// ����
	bool isEntered_;		// �v���C���[�������Ă�����
	bool isLetOut_;			// �v���C���[��ǂ��o������
};

#endif
