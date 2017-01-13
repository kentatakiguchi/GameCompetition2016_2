#ifndef ENEMY_MANAGER_H_
#define ENEMY_MANAGER_H_

//#include "../../../World/IWorld.h"
#include "../../../Math/Math.h"
#include <vector>
#include <map>

class FloorSearchPoint;

class EnemyManager{
public:
	EnemyManager(const Vector2 position, const Vector2& direction = Vector2(-1.0f, -1.0f));
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
	// �G����v���C���[�ɐL�΂����x�N�g����Ԃ��܂�
	Vector2 getPlayerVector();
	// �w�肵���I�u�W�F�N�g�Ƃ̕�����P�ʃx�N�g���Ŏ擾���܂�
	Vector2 getDirection(const Vector2& otherPosition);
	// �v���C���[�Ƃ̕�����P�ʃx�N�g���Ŏ擾���܂�
	Vector2 getPlayerDirection();
	// �w�肵���I�u�W�F�N�g�Ƃ̕������A���K�����ꂽ�x�N�g���Ŏ擾���܂�
	Vector2 getNormalizeDirection(const Vector2& otherPosition);
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
	// ���������߂邩
	void setIsDirection(bool isDirection);
	// �ǃI�u�W�F�N�g���񂵂āA���v�l��Ԃ��܂�
	int eachWSPObj();
	// �w�肵���v�f���̕Ǒ{���I�u�W�F�N�g���擾���܂�
	FloorSearchPoint* getWSPObj(const int number);
	// map�ɒǉ��������s���܂�
	void initWSPMap();
	// �ǈړ��̕��������肷�邩��Ԃ��܂�
	bool isDirecion();

private:
	int distance_;				// ����
	int wspResult_;				// �ǈړ��Ɏg���l�̍��v�l
	int wCollideCount_;			// �ǂɓ������Ă���I�u�W�F�N�g�̐�
	int wCollidePastCount_;		// �ǂɓ������Ă���I�u�W�F�N�g�̉ߋ��̐�
	float timer_;				// �o�ߎ���
	float deltaTimer_;			// ����
	float boxMoveCount;			// �l�p�`�ړ��J�E���g
	bool isDirection_;			// �����������邩
	Vector2 enemyPosition_;		// �G�̈ʒu
	Vector2 playerPosition_;	// �v���C���[�̈ʒu
	Vector2 threadPosition_;	// ���̈ʒu
	Vector2 enemyDirection_;
	Vector2 playerVector_;
	Vector2 wsDirection_;		// �ǈړ����̕���

	// �l�p�`�ړ��p�R���e�i
	typedef std::vector<float> WallMoveConteiner;
	WallMoveConteiner wallMoveConteiner_;
	// 
	typedef std::vector<FloorSearchPoint*> WSPContainer;
	WSPContainer wspContainer_;
	// �f���R���e�i
	typedef std::vector<int> PrimeContainer;
	PrimeContainer primeContainer_;
	// map
	typedef std::map<int, Vector2> WSPDirectionMap;
	WSPDirectionMap wspDirectionMap_;

// ���ړ��p
public:
	int threadLength_;
	float rotate_;
	float rotateSpeed_;
	float threadGravity_;
};

#endif