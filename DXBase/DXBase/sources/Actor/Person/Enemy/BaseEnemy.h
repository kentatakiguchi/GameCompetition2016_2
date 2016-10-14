#ifndef BASE_ENEMY_H_
#define BASE_ENEMY_H_

#include "../../Base/Actor.h"
#include "../../../Animation/Animation2D.h"
#include "../../../World/IWorld.h"
#include "../../../Math/Math.h"
#include <vector>

// ���[�V�����ԍ�(��)
enum {
	ENEMY_IDLE = 0,
	ENEMY_WALK = 1,
	ENEMY_ATTACK = 2,
	ENEMY_DAMAGE = 3,
	ENEMY_DEAD = 4
};

// ��ԗ�
enum class State {
	Idel,
	Search,
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
	BaseEnemy(IWorld* world, const Vector3&  position);
	~BaseEnemy();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;

protected:
	// �ҋ@��Ԃł�
	virtual void idle();
	// ���G�ړ����܂�
	virtual void searchMove();
	// �v���C���[��ǐՂ��܂�
	virtual void chaseMove();
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
	// �v���C���[�Ƃ̋�����Ԃ��܂�
	float playerLength();
	// �v���C���[�Ƃ̕�����P�ʃx�N�g���Ŏ擾���܂�
	Vector2 playerDirection();
	// �v���C���[�Ƃ̕����𐳋K�����ꂽ�x�N�g���Ŏ擾���܂�
	Vector3 playerNormalizeDirection();
	// �G�����ݍ��܂ꂽ���̃X�P�[���|�C���g��Ԃ��܂�
	float getSP();
	// �G�̑傫����Ԃ��܂�
	int getScale();

private:
	// ��Ԃ̍X�V���s���܂�
	void updateState(float deltaTime);

protected:
	// �����o�ϐ�
	int hp_;				// �̗�
	int ap_;				// �A�^�b�N�|�C���g
	float speed_;			// �ړ����x
	//Vector2 
	unsigned int color_;	// ���̂̐F
	float stateTimer_;		// ��ԃ^�C�}
	State state_;			// ���

	Vector2 target_;		// �^�[�Q�b�g�̈ʒu

	Animation2D animation_;	// �A�j���[�V����
	ActorPtr player_;			// �v���C���[
};

#endif