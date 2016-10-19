#ifndef BASE_ENEMY_H_
#define BASE_ENEMY_H_

#include "../../Base/Actor.h"
#include "../../../Animation/Animation2D.h"
#include "../../../World/IWorld.h"
#include "../../../Math/Math.h"
#include "EnemyManager.h"
#include <vector>

// ���[�V�����ԍ�(��)
enum {
	ENEMY_IDLE = 0,
	ENEMY_WALK = 1,
	ENEMY_DISCOVERY = 2,
	ENEMY_ATTACK = 3,
	ENEMY_DAMAGE = 4,
	ENEMY_DEAD = 5
};

// ��ԗ�
enum class State {
	Idel,
	Search,
	Discovery,
	Chase,
	/*PlayerShortDistance,
	PlayerCenterDistance,
	PlayerLongDistance,*/
	Attack,
	Damage,
	Dead,
	Return
};

//// ���S��ԗ�(�����Ԃ̎��S�ȂǂɑΉ��@���ݎg�p���Ȃ�)
//enum class DeadState {
//	KnockBackDead,
//	BlowAwayDead,
//	TornadoDead
//};

class BaseEnemy : public Actor {
public:
	BaseEnemy(IWorld* world, const Vector3&  position, const float bodyScale);
	~BaseEnemy();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;

protected:
	// �ҋ@��Ԃł�
	void idle();
	// ���G�ړ��ł�
	void search();
	// �v���C���[�𔭌��������̍s���ł�
	void discovery();
	// �v���C���[�̒ǐՍs���ł�
	virtual void chase();
	//// �v���C���[�Ƃ̋������Z���Ƃ��̍s���ł�
	//virtual void shortDistanceAttack();
	//// �v���C���[�Ƃ̋��������Ԃ̍s���ł�
	//virtual void centerDistanceAttack();
	//// �v���C���[�Ƃ̋����������Ƃ��̍s���ł�
	//virtual void longDistanceAttack();
	// �U���s���ł�
	virtual void Attack();
	// ��e�s���ł�
	void damageMove();
	// ���S�s���ł�
	void deadMove();
	// ��Ԃ̕ύX���s���܂�
	void changeState(State state, unsigned int motion);
	//// �G�̎��S��Ԃ̕ύX���s���܂�
	//void changeDeadState(EnemyDeadState state);
	// �v���C���[��{�����܂�
	void findPlayer();
	//// �v���C���[�̒ǐՂ𒆎~���鋗���̉��Z�ł�
	//void AddPlayerChaseStopDistance(float distance);

protected:
	// ���G���̍s���ł�
	virtual void searchMove();
	// �ǐՎ��̍s���ł�
	virtual void chaseMove();

public:
	// �G�����ݍ��܂ꂽ���̃X�P�[���|�C���g��Ԃ��܂�
	float getSP();
	// �G�̑傫����Ԃ��܂�
	int getScale();

private:
	// ��Ԃ̍X�V���s���܂�
	void updateState(float deltaTime);

protected:
	// �����o�ϐ�
	int hp_;						// �̗�
	int ap_;						// �A�^�b�N�|�C���g
	float speed_;					// �ړ����x
	float initSpeed_;				// �����̈ړ����x
	float discoveryLenght_;			// �v���C���[�ɋC�Â�����

	unsigned int color_;			// ���̂̐F
	float stateTimer_;				// ��ԃ^�C�}
	std::string stateString_;		// ��Ԃ̕�����i�f�o�b�O�p�j
	State state_;					// ���
	Vector2 target_;				// �^�[�Q�b�g�̈ʒu
	Vector3 discoveryPosition_;		// ���������Ƃ��̈ʒu

	Animation2D animation_;			// �A�j���[�V����
	ActorPtr player_;				// �v���C���[

	EnemyManager enemyManager_;
};

#endif