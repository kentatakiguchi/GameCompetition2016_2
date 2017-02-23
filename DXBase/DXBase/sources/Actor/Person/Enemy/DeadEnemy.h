#ifndef DEADENEMY_H_
#define DEADENEMY_H_

#include "../../Base/Actor.h"
#include "../../../Animation/Enemy/EnemyAnimation2D.h"
#include "../../../ResourceLoader/ResourceLoader.h"

// ���S�G�l�~�[(�Փ˔���̂�)
class DeadEnemy : public Actor {
private:
	enum class State {
		Dead,
		Hold,
		Throw,
		Delete,
	};

public:
	DeadEnemy(
		IWorld* world,
		const Vector2&  position,
		const float bodyScale,
		const Vector2& direction = Vector2(1.0f, 1.0f),
		const AnimationID animaID = AnimationID::ENEMY_EGGENEMY_DAMAGE_TEX);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

private:
	// ��Ԃ̍X�V
	void updateState(float deltaTime);
	// ��Ԃ̕ύX
	void changeState(State state);
	// ���S���
	void deadMove();
	// �����グ���
	void holdMove(float deltaTime);
	// �������
	void throwMove(float deltaTime);
	// ���ŏ��
	void deleteMove(float deltaTime);
	// �Փ˔���̍X�V
	void updateCollide();
	// �n�ʂ̈ʒu�ɕ␳���܂�
	void groundClamp(Actor& actor);
	// �v���C���[�̖��O��ݒ肵�܂�
	void setPlayerName();

private:
	float stateTimer_;				// ��ԃ^�C�}
	bool isGround_;					// �ڒn���Ă��邩
	EnemyAnimation2D animation_;	// �A�j���[�V����
	State state_;					// ���

	int starCount_;
	float playerSpeed_;				// �v���C���[�̈ړ����x
	float holdLength_;				// ���܂ꂽ�ʒu�Ƃ̋���
	float throwDegree_;				// ������ꂽ���̊p�x
	Vector2 playerPravPosition_;	// �v���C���[�̑O��̈ʒu
	Vector2 holdPosition_;			// ���܂ꂽ�ʒu
	Vector2 prevPosition_;			// �O��̈ʒu
	Vector2 throwVector_;			// ������ꂽ�Ƃ��̃x�N�g��
	bool isHold_;					// ���܂��Ă��邩
	std::string playerName_;		// ���񂾑���̖��O
	std::string otherName_;			// �����Е��̖��O

private:
	bool isBlockCollideBegin_;		// �u���b�N�Ɠ������Ă��邩(����)
	bool isBlockCollideEnter_;		// �u���b�N�Ɠ������Ă��邩(�Փ˒�)
	bool isBlockCollidePrevEnter_;	// �u���b�N�Ɠ������Ă��邩(�ߋ��̏Փ˒�)
	bool isBlockCollideExit_;		// �u���b�N�Ɠ������Ă��邩(�Փˌ�)
};

#endif
