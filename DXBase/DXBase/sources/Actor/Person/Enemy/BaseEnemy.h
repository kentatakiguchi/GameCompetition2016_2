#ifndef BASE_ENEMY_H_
#define BASE_ENEMY_H_

#include "../../Base/Actor.h"
#include "EnemyManager.h"
#include "../../../Animation/Enemy/EnemyAnimation2D.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include <vector>

class CollisionBase;
class FloorSearchPoint;
class Prickle;

class BaseEnemy : public Actor {
protected:
	// �A�j���[�V����ID
	enum {
		ENEMY_WALK = 0,
		ENEMY_WALKTURN = 4,
		ENEMY_DISCOVERY = 3,
		ENEMY_ATTACK = 1,
		ENEMY_ATTACKTURN = 5,
		ENEMY_DAMAGE = 2,
	};
	//// �G�t�F�N�gID
	//enum {
	//	EFFECT_DEAD = 0
	//};
	// SEID
	enum {
		SE_HAKKEN = 0,
		SE_HITSTOP = 1,
		SE_DEAD = 2
	};
	// �v���C���[�ԍ�
	enum {
		PLAYER_RED_NUMBER = 0,
		PLAYER_BLUE_NUMBER = 1
	};
	// ��ԗ�
	enum class State {
		Idel,
		Search,
		Discovery,
		Chase,
		Lost,
		attack,
		Damage,
		Dead,
		Return
	};

public:
	// ��`
	BaseEnemy(
		IWorld* world,
		const Vector2&  position,
		const float bodyScale,
		const Vector2& direction = Vector2(1.0f, 1.0f));
	~BaseEnemy();
	void Initialize();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;

protected:
	// �q���p��update(�e��update�O�ɍs���܂�)
	virtual void beginUpdate(float deltaTime);
	// �q���p��update
	virtual void update(float deltaTime);
	// �ҋ@��Ԃł�
	void idle();
	// ���G�ړ��ł�
	virtual void search();
	// �v���C���[�𔭌��������̍s���ł�
	virtual void discovery();
	// �v���C���[�̒ǐՍs���ł�
	virtual void chase();
	// �U���s���ł�
	virtual void attack();
	// ��e�s���ł�
	void damageMove();
	// ���S�s���ł�
	void deadMove();
	// �v���C���[�����������Ƃ��̍s���ł�
	virtual void lostMove();
	// ��Ԃ̕ύX���s���܂�
	void changeState(State state, unsigned int motion);
	// �������Ă���I�u�W�F�N�g�̈ʒu��ݒ肵�܂�
	virtual void setObjPosition();
	// �v���C���[��{�����܂�
	void findPlayer();

protected:
	// ���G���̍s���ł�
	virtual void searchMove();
	// �ǐՎ��̍s���ł�
	virtual void chaseMove();
	// ���{���I�u�W�F�N�g�̐���
	void createFSP();
	// �f���^�^�C��(�ő�l1)�̐ݒ�
	void setDeltaTime(float deltatime);

public:
	// �G�����ݍ��܂ꂽ���̃X�P�[���|�C���g��Ԃ��܂�
	float getSP();
	// �G�̑傫����Ԃ��܂�
	int getScale();

protected:
	// ��Ԃ̍X�V���s���܂�
	void updateState(float deltaTime);
	// �{���I�u�W�F�N�g�֘A�̍X�V
	void updateSearchObjct();
	// �Փˊ֘A�̍X�V
	void updateCollide();
	// �n�ʂ̈ʒu�ɕ␳���܂�
	void groundClamp(Actor& actor);
	// �~�ƏՓ˂����Ƃ��Ɉʒu�ɕ␳���܂�
	void circleClamp(Actor& actor);
	// �A�j���[�V�����̒ǉ����s���܂�
	virtual void addAnimation();
	// �v���C���[�Ƃ�X������Y�������v�Z���A��ʊO�ɂ��邩��Ԃ��܂�
	bool isScreen();
	// �|�[�Y����SE�̒�~���s���܂�
	void poseStopSE();
	// �|�[�Y��������SE���ēx�Đ����܂�
	void poseRestartSE();

protected:
	// �����o�ϐ�
	float timer_;					// ���݂̎���(���)
	float deltaTimer_;				// ���݂̎���(���, �ő�l 1)
	int hp_;						// �̗�
	int ap_;						// �A�^�b�N�|�C���g
	int texSize_;					// �e�N�X�`����؂蔲������傫��
	int turnMotion_;
	int discoveryNumber_;			// �����ԍ�
	float speed_;					// �ړ����x
	float initSpeed_;				// �����̈ړ����x
	float scale_;					// �傫��
	float playerLength_;			// �v���C���[�Ƃ̋���
	float discoveryLenght_;			// �v���C���[�ɋC�Â�����
	float playerLostLenght_;		// �v���C���[������������
	float texDegress_;				// �e�N�X�`���̊p�x
	float hitTimer_;				// �Փˎ��̎���
	Vector2 direction_;				// ����
	Vector2 prevDirection_;			// �ߋ��̕���
	bool isPlayer_;					// �v���C���[�����݂���̂�
	bool isMove_;					// ������
	bool isScreen_;					// ��ʓ��ɂ��邩
	bool isBlockCollideBegin_;		// �u���b�N�Ɠ������Ă��邩(����)
	bool isBlockCollideEnter_;		// �u���b�N�Ɠ������Ă��邩(�Փ˒�)
	bool isBlockCollidePrevEnter_;	// �u���b�N�Ɠ������Ă��邩(�ߋ��̏Փ˒�)
	bool isBlockCollideExit_;		// �u���b�N�Ɠ������Ă��邩(�Փˌ�)
	bool isGround_;					// �ڒn���Ă��邩 true�Őڒn���Ă��܂�
	bool isUseGravity_;				// �d�͂��g���� true�ŏd�͂�ǉ����܂�
	bool isInvincible_;				// ���G�� true�Ŗ��G�ɂȂ�܂�
	bool isLostChase_;				// �������Ă��ǂ��� true�Ńv���C���[���͈͊O�ɏo�Ă��A�ǐՍs�����s���܂�
	bool isMoveFloor_;				// �����Ă��鏰�ɐG��Ă��邩
	float stateTimer_;				// ��ԃ^�C�}
	State state_;					// ���
	Vector2 discoveryPosition_;		// ���������Ƃ��̈ʒu
	Vector2 addTexPosition_;		// �e�N�X�`���̕\���ʒu�̒ǉ�
	EnemyManager enemyManager_;		// �G�l�~�[�}�l�[�W���[
	FloorSearchPoint* fspScript_;	// ���{���I�u�W�F�N�g
	FloorSearchPoint* wsScript_;		// �Ǒ{���I�u�W�F�N�g
	Prickle* pricleObj_;			// �g�Q�̃I�u�W�F�N�g
	EnemyAnimation2D animation_;	// �A�j���[�V����
	AnimationID deadAnimaID_;		// ���S���̃A�j���[�V����
	// �{���I�u�W�F�N�g�̈ʒu�R���e�i
	typedef std::vector<Vector2> FSPPositionContainer;
	FSPPositionContainer fspPositionContainer_;
	// �{���I�u�W�F�N�g�̑傫���R���e�i
	typedef std::vector<Vector2> FSPScaleContainer;
	FSPScaleContainer fspScaleContainer_;
	// �������Ă���I�u�W�F�N�g�̃R���e�i
	typedef std::list<Actor*> ObjContainer;
	ObjContainer objContainer_;
	// SE�n���h���R���e�i
	typedef std::vector<int> SEContainer;
	SEContainer seHandles_;
	// �Đ�SE�n���h���R���e�i
	typedef std::list<int> PlaySEContainer;
	PlaySEContainer playSEHandles_;
	// �d�͉����x
	const float GRAVITY_ = 9.8f;
};

#endif