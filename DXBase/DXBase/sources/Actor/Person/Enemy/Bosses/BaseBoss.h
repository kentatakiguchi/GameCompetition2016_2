#ifndef BASE_BOSS_H_
#define BASE_BOSS_H_

#include "../../../Base/Actor.h"
#include "../../../../World/IWorld.h"
#include "../../../../Math/Math.h"
#include "../../../../Define.h"
#include "../../../../Animation/Enemy/EnemyAnimation2D.h"
#include "BossAnimationNumber.h"
#include "BossManager.h"

class FloorSearchPoint;
class BossEntry;
class BossHeart;
class BossGaugeUI;

// �{�X�N���X
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
		BattleIdel,
		Idel,
		Attack,
		Damage,
		Flinch,
		Piyori,
		Boko,
		Dead
	};
	// �U����Ԃ̗�
	enum class AttackState {
		JumpAttack,
		WallAttack,
		SpeacialAttack
	};

public:
	BaseBoss(
		IWorld* world,
		const Vector2&  position,
		const float bodyScale = 128.0f);// * 2 / 2.0f);
	~BaseBoss();
	virtual void onUpdate(float deltaTime) override;
	virtual void onEnd();
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;

public:
	// �V�[�����I�������邩��Ԃ��܂�
	bool isSceneEnd();
	// �ړI�n�Ɉړ����܂�
	void movePosition(float deltaTime);
	// �ړI�̈ʒu��ݒ肵�܂�
	void setMovePosition(const Vector2& position, const float speed);
	// �ړI�̈ʒu�ɓ��B��������Ԃ��܂� (�ړI�̈ʒu, ���x)
	bool isMovePosition();
	// �퓬���J�n���邩��Ԃ��܂�
	void setIsBattle(bool isBattle);

protected:
	// ��Ԃ̍X�V
	void updateState(float deltaTime);
	// ��Ԃ̕ύX���s���܂�
	void changeState(State state, int num);
	// �U����Ԃ̕ύX���s���܂�
	void changeAttackState(AttackState aState, int num);
	// �퓬�ҋ@���
	void battleIdel(float deltaTime);
	// �ҋ@���
	virtual void idel(float deltaTime);
	// �U���s��
	void attack(float deltaTime);
	// �_���[�W���
	void damage(float deltaTime);
	// ���ݏ��
	void flinch(float deltaTime);
	// �҂���� // �҂��[�����b�N����
	void piyori(float deltaTime);
	// �ڂ�����
	void boko(float deltaTime);
	// ���S���
	void deadMove(float deltaTime);
	// �҂��s��
	void piyoriMove(float deltaTime);

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
	// �w�肵���l�̃_���[�W�ʂ����Z���܂�
	void damage(
		const int damage,
		const Vector2& position, 
		const float scale = 1.0f);
	//�n�ʂ̈ʒu�ɕ␳���܂�
	void groundClamp(Actor& actor);
	// �A�j���[�V�����̒ǉ�
	void addAnimation();
	// �҂���Ԃ̐ݒ���s���܂�
	void setPiyori();

protected:
	int dp_;						// �ϋv�l
	int hp_;						// �̗�
	unsigned int attackCount_;		// �U���s������J�E���g
	int flinchCount_;				// �Ђ�ނ܂ł̉�
	int piyoriCount_;				// �҂���
	int bokoCreateCount_;			// �{�R�G�t�F�N�g������
	float stateTimer_;				// ��Ԃ̎���
	float timer_;					// ���݂̎���(�ő�l 1)
	float deltaTimer_;				// ���݂̎���(���)
	float damageTimer_;				// ���ɔ�e�܂ł̎���
	float angle_;					// �p�x(���v����)
	float effectCreateTimer_;		// �G�t�F�N�g��������(�Ԋu)
	bool isGround_;					// �ڒn���Ă��邩
	bool isBottomHit_;				// �ǂ̉����ɓ���������
	//bool isHit_;					// �v���C���[�{�̂ɓ����邩
	bool isAttackHit_;				// �v���C���[�̍U���ɓ����邩
	bool isSceneEnd_;				// �V�[�����I�������邩
	bool isBattle_;					// �퓬���s����
	bool isEffectCreate_;			// �G�t�F�N�g�𐶐����邩
	int handle_;					// �f�o�b�O�n���h��
	FloorSearchPoint* wspObj_;		// �Ǒ{���I�u�W�F�N�g
	BossEntry* entryObj_;			// �{�X�����I�u�W�F�N�g
	BossManager bossManager_;		// �{�X�}�l�[�W���[
	// �U����Ԃ̃R���e�i
	typedef std::vector<AttackState> AttackStateContainer;
	AttackStateContainer asContainer_;
	// �U�����[�V�����R���e�i
	typedef std::vector<int> BossAnimationContainer;
	BossAnimationContainer asAnimations_;

private:
	Vector2 playerPastPosition_;	// �v���C���[�̉ߋ��̈ʒu
	Vector2 direction_;				// ����
	ActorPtr player_;
	State state_;					// ���
	AttackState attackState_;		// �U�����
	int animeNum_;
	EnemyAnimation2D animation_;	// �A�j���[�V����
	BossGaugeUI* bossGaugeUI_;		// �{�X�̗̑�

	float top_, bottom_, right_, left_;	// ����p

	Vector2 movePos_;
	float moveSpeed_;
	// �N�����v�p�̈ʒu(��)
	const Vector2 FIELD_SIZE = Vector2(
		SCREEN_SIZE.x - CHIPSIZE - body_.GetCircle().getRadius(), 
		SCREEN_SIZE.y - CHIPSIZE - body_.GetCircle().getRadius());
	// �̗͂̃��b�N�R���e�i
	typedef std::vector<int> LockHpContainer;
	LockHpContainer lockHps_;
	// �X�^�[�G�t�F�N�g�p�R���e�i
	typedef std::list<ActorPtr> StarContainer;
	StarContainer stars_;
};

#endif
