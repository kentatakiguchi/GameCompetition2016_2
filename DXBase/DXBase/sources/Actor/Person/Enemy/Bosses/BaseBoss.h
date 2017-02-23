#ifndef BASE_BOSS_H_
#define BASE_BOSS_H_

#include "../../../Base/Actor.h"
#include "../../../../Animation/Enemy/EnemyAnimation2D.h"
#include "BossAnimationNumber.h"
#include "BossManager.h"
#include "MiniBossManager.h"
#include <random>

class FloorSearchPoint;
class BossEntry;
class BossGaugeUI;

// �{�X�N���X
class BaseBoss : public Actor {
protected:
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
		Dead,
		LiftIdel,
		LiftMove
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
	// ���̊l������ݒ肵�܂�
	void setStarCount(const int count, const int all);

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
	// �����グ�ҋ@���
	void liftIdel(float deltaTime);
	// �����グ�ړ����
	void liftMove(float deltaTime);

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
	// �{�X�̃A���t�@�l��ݒ肵�܂�
	void texAlpha(float deltaTime);
	// �|�[�Y����SE�̒�~���s���܂�
	void poseStopSE();
	// �|�[�Y��������SE���ēx�Đ����܂�
	void poseRestartSE();
	// ���V�~�j�{�X�̐������s���܂�
	void createMiniBoss();
	// �����_���̒l���擾���܂�
	int getRandomInt(const int min, const int max);
	// �R���e�i�̏�����
	void initContainer();
	// �I�u�W�F�N�g�̐���
	void createObject();

protected:
	int dp_;						// �ϋv�l
	int hp_;						// �̗�
	unsigned int attackCount_;		// �U���s������J�E���g
	unsigned int currentACount_;
	int flinchCount_;				// �Ђ�ނ܂ł̉�
	int piyoriCount_;				// �҂���
	int bokoCreateCount_;			// �{�R�G�t�F�N�g������
	int miniBossCreateCount_;		// �~�j�{�X������
	int starCount_;					// �v���C���[�̎擾���Ă��鐯�̍��v��
	int allStarCount_;				// �S�̂ł̐��̍��v��
	float stateTimer_;				// ��Ԃ̎���
	float timer_;					// ���݂̎���(�ő�l 1)
	float deltaTimer_;				// ���݂̎���(���)
	float liftMoveTiemr_;			// �����グ���̎���
	float angle_;					// �p�x(���v����)
	float effectCreateTimer_;		// �G�t�F�N�g��������(�Ԋu)
	float mbTimer_;					// �~�j�{�X��������
	float liftCount_;				// �����グ�J�E���g
	float bgmVolume_;				// BGM�̉���
	bool isGround_;					// �ڒn���Ă��邩
	bool isBottomHit_;				// �ǂ̉����ɓ���������
	bool isAttackHit_;				// �v���C���[�̍U���ɓ����邩
	bool isSceneEnd_;				// �V�[�����I�������邩
	bool isBattle_;					// �퓬���s����
	bool isEffectCreate_;			// �G�t�F�N�g�𐶐����邩
	bool isACountDecision_;			// 
	bool isPlayerCollide_;			// �v���C���[���Փ˔�����s����
	bool isBossDead_;				// ���S������
	FloorSearchPoint* wspObj_;		// �Ǒ{���I�u�W�F�N�g
	BossEntry* entryObj_;			// �{�X�����I�u�W�F�N�g
	MiniBossManager mbManager_;
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
	std::mt19937 mt_;				// �����̏���seed

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
	// SE�n���h���R���e�i
	typedef std::list<int> SEContainer;
	SEContainer seHandles_;
	// �Đ�SE�n���h���R���e�i
	typedef std::list<int> PlaySEContainer;
	PlaySEContainer playSEHandles_;
};

#endif
