#ifndef ENEMY_MANAGER_H_
#define ENEMY_MANAGER_H_

//#include "../../../World/IWorld.h"
#include "../../../Math/Math.h"
#include <vector>
#include <map>

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
	// �w�肵���I�u�W�F�N�g�Ƃ̋�����Ԃ��܂�
	float getLength(const Vector2& otherPosition);
	// �v���C���[�Ƃ̋�����Ԃ��܂�
	float getPlayerLength();
	// �w�肵���I�u�W�F�N�g�Ƃ̕�����P�ʃx�N�g���Ŏ擾���܂�
	Vector2 getDirection(const Vector2& otherPosition);
	// �v���C���[�Ƃ̕�����P�ʃx�N�g���Ŏ擾���܂�
	Vector2 getPlayerDirection();
	// �v���C���[�Ƃ̕����𐳋K�����ꂽ�x�N�g���Ŏ擾���܂�
	Vector2 getPlayerNormalizeDirection();
	//�@�G���g�ƃv���C���[�̈ʒu�����܂�
	void setEMPosition(const Vector2& enemyPosition, const Vector2& playerPosition, const Vector2 direction);
	// ���̎x�_�̈ʒu�擾
	Vector2 getThreadPoint();
	// �{���I�u�W�F�N�g�̐ݒ�
	void addFSP(FloorSearchPoint* fsp);
	// �ǂɉ�����������
	Vector2 getWallDirection();
	// �ǃI�u�W�F�N�g���񂵂āA���v�l��Ԃ��܂�
	float eachWSPObj();
	// �w�肵���v�f���̕Ǒ{���I�u�W�F�N�g���擾���܂�
	FloorSearchPoint* getWSPObj(const int number);

private:
	int distance_;				// ����
	float timer_;				// �o�ߎ���
	float deltaTimer_;			// ����
	float boxMoveCount;			// �l�p�`�ړ��J�E���g
	float wspResult_;			// �ǈړ��Ɏg���l�̍��v�l

	Vector2 enemyPosition_;		// �G�̈ʒu
	Vector2 playerPosition_;	// �v���C���[�̈ʒu
	Vector2 threadPosition_;	// ���̈ʒu
	Vector2 enemyDirection_;

	Vector2 wsDirection_;

	// �l�p�`�ړ��p�R���e�i
	typedef std::vector<float> WallMoveConteiner;
	WallMoveConteiner wallMoveConteiner_;
	// 
	typedef std::vector<FloorSearchPoint*> WSPContainer;
	WSPContainer wspContainer_;
	// map
	typedef std::map<float, Vector2> WSPDirectionMap;
	WSPDirectionMap wspDirectionMap_;

// ���ړ��p
//private:
public:
	int threadLength_;
	float rotate_;
	float rotateSpeed_;
	float threadGravity_;
};

#endif