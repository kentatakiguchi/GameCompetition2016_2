#ifndef ENEMY_MANAGER_H_
#define ENEMY_MANAGER_H_

//#include "../../../World/IWorld.h"
#include "../../../Math/Math.h"
#include <vector>

class FloorSearchPoint;

class EnemyManager{
public:
	EnemyManager(const Vector2 position);
	~EnemyManager();
	// �X�V
	void update(float deltaTime);
	// ���̓�����(�ǂȂ�)
	Vector2 boxMove();
	// �ǂɉ������������i�܂��j
	Vector2 wallMove();
	// �R������铮����
	Vector2 cliffMove(bool isFloor);
	// �����g����������
	Vector2 threadMove();
	// �v���C���[�Ƃ̋�����Ԃ��܂�
	float getPlayerLength();
	// �v���C���[�Ƃ̕�����P�ʃx�N�g���Ŏ擾���܂�
	Vector2 getPlayerDirection();
	// �v���C���[�Ƃ̕����𐳋K�����ꂽ�x�N�g���Ŏ擾���܂�
	Vector2 getPlayerNormalizeDirection();
	//�@�G���g�ƃv���C���[�̈ʒu�����܂�
	void setEMPosition(const Vector2& enemyPosition, const Vector2& playerPosition);
	// ���̎x�_�̈ʒu�擾
	Vector2 getThreadPoint();
	// �{���I�u�W�F�N�g�̐ݒ�
	void addFSP(FloorSearchPoint* fsp);
	// �ǂɉ�����������
	Vector2 getWallDirection();

private:
	int distance_;				// ����

	float timer_;				// �o�ߎ���
	float deltaTimer_;			// ����
	float boxMoveCount;			// �l�p�`�ړ��J�E���g

	Vector2 enemyPosition_;		// �G�̈ʒu
	Vector2 playerPosition_;	// �v���C���[�̈ʒu
	Vector2 threadPosition_;	// ���̈ʒu

	// �l�p�`�ړ��p�R���e�i
	typedef std::vector<float> BoxMoveConteiner;
	BoxMoveConteiner boxMoveConteiner_;
	// 
	typedef std::vector<FloorSearchPoint*> FSPContainer;
	FSPContainer fspContainer_;

// ���ړ��p
//private:
public:
	int threadLength_;
	float rotate_;
	float rotateSpeed_;
	float threadGravity_;
};

#endif