#ifndef WALL_ATTACK_H_
#define WALL_ATTACK_H_

#include "BossAttack.h"
#include <vector>

// �ǈړ��U��
class WallAttack : public BossAttack {
private:
	enum class State {
		FloorSearch,
		FloorGetOff,
		WallMove,
		WallAttackMove
	};

public:
	WallAttack();
	WallAttack(IWorld* world, const Vector2& position);
	// �U��
	virtual void attack(float deltaTime) override;
	// �U���s���̃��t���b�V�����s���܂�
	virtual void Refresh() override;

private:
	// ���{����Ԃł�
	void floorSearch(float deltaTime);
	// ������~����Ԃł�
	void floorGetOff(float deltaTime);
	// �ǈړ���Ԃł�
	void wallMove(float deltaTime);
	// �ǍU����Ԃł�
	void wallAttackMove(float deltaTime);
	// �ǈړ����鎞�Ԃ����肵�܂�
	void setAttackSecond();
	// ��Ԃ̕ύX���s���܂�
	void changeState(State state, int number);

protected:
	int count_;						// �����]���J�E���g
	int aSecond_;					// �U����ԂɑJ�ڂ���b���ł�
	int createCount_;				// �G�t�F�N�g������
	float speed_;					// �ړ����x
	bool isWallAttackEnd_;			// �ǍU�����I�������
	State state_;					// ���
	Vector2 prevPlayerDistance_;	// �ߋ��̃v���C���[�̕���
	// �ǈړ����ԃR���e�i
	typedef std::vector<int> MoveTimeContainer;
	MoveTimeContainer moveTimes_;
	// �����R���e�i
	typedef std::vector<float> MoveDirectionContainer;
	MoveDirectionContainer moveDirections_;
};

#endif
