#ifndef BASE_BOSS_H_
#define BASE_BOSS_H_

#include "../../../Base/Actor.h"
#include "../../../../Animation/Animation2D.h"
#include "../../../../World/IWorld.h"
#include "../../../../Math/Math.h"
#include "../../../../Define.h"

#include "BossManager.h"

// class BossManager;
class FloorSearchPoint;
class BossEntry;
class BossHeart;
class BossGaugeUI;

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

public:
	// �V�[�����I�������邩��Ԃ��܂�
	bool isSceneEnd();

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
	// �{�X�}�l�[�W���[�̃X�e�[�^�X�̐ݒ�
	void setBMStatus();
	//�n�ʂ̈ʒu�ɕ␳���܂�
	void groundClamp(Actor& actor);

protected:
	int dp_;					// �Ђ�ނ܂ł̑ϋv�l
	int initDp_;				// �Ђ�ނ܂ł̑ϋv�l(�����l)
	int hp_;					// �̗�
	int flinchCount_;			// �Ђ�ނ܂ł̉�
	// int initHp_;				// �̗�(�����l)
	float stateTimer_;			// ��Ԃ̎���
	float timer_;				// ���݂̎���(�ő�l 1)
	float deltaTimer_;			// ���݂̎���(���)

	bool isGround_;				// �ڒn���Ă��邩
	bool isSceneEnd_;			// �V�[�����I�������邩

	std::string stateString_;	// ��Ԃ̕�����i�f�o�b�O�p�j

	FloorSearchPoint* fspObj_;	// ���{���I�u�W�F�N�g
	BossEntry* entryObj_;		// �{�X�����I�u�W�F�N�g
	BossHeart* heartObj_;		// �{�X�S���I�u�W�F�N�g
	BossManager bossManager_;	// �{�X�}�l�[�W���[
	// �U����Ԃ̃R���e�i
	typedef std::vector<AttackState> AttackStateContainer;
	AttackStateContainer asContainer_;

private:
	Vector2 playerPastPosition_;
	ActorPtr player_;

	State state_;				// ���
	AttackState attackState_;	// �U�����

	BossGaugeUI* bossGaugeUI_;	// �{�X�̗̑�

	// �N�����v�p�̈ʒu(��)
	const Vector2 FIELD_SIZE = Vector2(
		SCREEN_SIZE.x - CHIPSIZE - body_.GetCircle().getRadius(), 
		SCREEN_SIZE.y - CHIPSIZE - body_.GetCircle().getRadius());
};

#endif
