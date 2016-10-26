#ifndef ENEMY_MANAGER_H_
#define ENEMY_MANAGER_H_

//#include "../../../World/IWorld.h"
#include "../../../Math/Math.h"
#include <vector>

class FloorSearchPoint;

class EnemyManager{
public:
	EnemyManager(const Vector3 position);
	~EnemyManager();
	// �X�V
	void update(float deltaTime);
	// ���̓�����(�ǂȂ�)
	Vector3 boxMove();
	// �ǂɉ������������i�܂��j
	Vector3 wallMove();
	// �R������铮����
	Vector3 cliffMove(bool isFloor);
	// �����g����������
	Vector3 threadMove();
	// �v���C���[�Ƃ̋�����Ԃ��܂�
	float getPlayerLength();
	// �v���C���[�Ƃ̕�����P�ʃx�N�g���Ŏ擾���܂�
	Vector2 getPlayerDirection();
	// �v���C���[�Ƃ̕����𐳋K�����ꂽ�x�N�g���Ŏ擾���܂�
	Vector3 getPlayerNormalizeDirection();
	//�@�G���g�ƃv���C���[�̈ʒu�����܂�
	void setEMPosition(const Vector3& enemyPosition, const Vector3& playerPosition);
	// ���̎x�_�̈ʒu�擾
	Vector3 getThreadPoint();
	// �{���I�u�W�F�N�g�̐ݒ�
	void addFSP(FloorSearchPoint* fsp);
	// �ǂɉ�����������
	Vector3 getWallDirection();

private:
	int distance_;				// ����

	float timer_;				// �o�ߎ���
	float deltaTimer_;			// ����
	float boxMoveCount;			// �l�p�`�ړ��J�E���g

	Vector3 enemyPosition_;		// �G�̈ʒu
	Vector3 playerPosition_;	// �v���C���[�̈ʒu
	Vector3 threadPosition_;	// ���̈ʒu

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