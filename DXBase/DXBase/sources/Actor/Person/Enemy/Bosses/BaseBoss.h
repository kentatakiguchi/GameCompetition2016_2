#ifndef BASE_BOSS_H_
#define BASE_BOSS_H_

#include "../../../Base/Actor.h"
#include "../../../../Animation/Animation2D.h"
#include "../../../../World/IWorld.h"
#include "../../../../Math/Math.h"
#include "../../../../Define.h"

#include "BossManager.h"

// class BossManager;

class BaseBoss : public Actor {
protected:
	// ���[�V�����ԍ�
	enum {
		BOSS_IDLE = 0,
		BOSS_ATTACK = 1,
		BOSS_FLINCH = 2,
		BOSS_DEAD = 3,
	};
	// �U���s���̔ԍ�
	enum {
		ATTACK_JUMPATTACK_NUMBER = 0,
		ATTACK_WALLATTACK_NUMBER = 1,
		ATTACK_SPECIALATTACK_NUMBER = 2
	};
	// ��ԗ�
	enum class State {
		Idel,
		//Search,
		Attack,
		Flinch,
		Dead
	};
	// �U����Ԃ̗�
	enum class AttackState {
		JumpAttack,
		WallAttack,
		SpeacialAttack
	};

public:
	BaseBoss(IWorld* world, const Vector2&  position, const float bodyScale);
	~BaseBoss();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;

protected:
	// ��Ԃ̍X�V
	void updateState(float deltaTime);
	// ��Ԃ̕ύX���s���܂�
	void changeState(State state, unsigned int motion);
	// �U����Ԃ̕ύX���s���܂�
	void changeAttackState(AttackState aState, unsigned int motion);
	// �ҋ@���
	void idel(float deltaTime);
	// �U���s��
	void attack(float deltaTime);
	// �Ђ�ݏ��
	void flinch(float deltaTime);
	// ���S���
	void deadMove(float deltaTime);

// �U���s��
protected:
	// �W�����v�U��
	void jumpAttack(float deltaTime);
	// �ǍU��
	void wallAttack(float deltaTime);
	// �X�y�V�����A�^�b�N
	void specialAttack(float deltaTime);

private:
	// �f���^�^�C��(�ő�l1)�̐ݒ�
	void setTimer(float deltaTime);

protected:
	int dp_;					// �Ђ�ނ܂ł̑ϋv�l
	int initDp_;				// �Ђ�ނ܂ł̑ϋv�l(�����l)
	int hp_;					// �̗�
	float stateTimer_;			// ��Ԃ̎���
	float timer_;				// ���݂̎���(�ő�l 1)
	float deltaTimer_;			// ���݂̎���(���)

	std::string stateString_;	// ��Ԃ̕�����i�f�o�b�O�p�j

	// BossManager* bossManager_;	// �{�X�}�l�[�W���[
	BossManager bossManager_;

private:
	Vector2 playerPastPosition_;
	ActorPtr player_;

	State state_;				// ���
	AttackState attackState_;	// �U�����
};

#endif
