#ifndef ENEMY_MANAGER_H_
#define ENEMY_MANAGER_H_

#include "../../../Math/Math.h"
#include <vector>
#include <map>

class FloorSearchPoint;
class PlayerSearchObj;
class IWorld;

class EnemyManager{
public:
	EnemyManager(
		IWorld* world,
		const Vector2 position, 
		const Vector2& direction = Vector2(-1.0f, -1.0f));
	~EnemyManager();
	// �X�V
	void update(float deltaTime);
	// �ǂɉ������������i�܂��j
	Vector2 wallMove();
	// �R������铮����
	Vector2 cliffMove(bool isFloor);
	// �v���C���[�̈ʒu���擾���܂�
	Vector2 getPlayerPosition(const int number);
	// �w�肵���I�u�W�F�N�g�Ƃ̋�����Ԃ��܂�
	float getLength(const Vector2& otherPosition);
	// �v���C���[�Ƃ̋�����Ԃ��܂�
	float getPlayerLength(const int number);
	// �G����v���C���[�ɐL�΂����x�N�g����Ԃ��܂�
	Vector2 getPlayerVector(const int number);
	// �w�肵���I�u�W�F�N�g�Ƃ̕�����P�ʃx�N�g���Ŏ擾���܂�
	Vector2 getDirection(const Vector2& otherPosition);
	// �v���C���[�Ƃ̕�����P�ʃx�N�g���Ŏ擾���܂�
	Vector2 getPlayerDirection(const int number);
	// �w�肵���I�u�W�F�N�g�Ƃ̕������A���K�����ꂽ�x�N�g���Ŏ擾���܂�
	Vector2 getNormalizeDirection(const Vector2& otherPosition);
	// �v���C���[�Ƃ̕����𐳋K�����ꂽ�x�N�g���Ŏ擾���܂�
	Vector2 getPlayerNormalizeDirection(const int number);
	//�@�G���g�ƃv���C���[�̈ʒu�����܂�
	void setEMPosition(
		const Vector2& enemyPosition,
		const Vector2& direction);
	// ���̎x�_�̈ʒu�擾
	Vector2 getThreadPoint();
	// �{���I�u�W�F�N�g�̐ݒ�
	void addFSP(FloorSearchPoint* fsp);
	// �ǂɉ�����������
	Vector2 getWallDirection();
	// �ǈړ����̃A�j���[�V�����̕������擾���܂�
	Vector2 getWallAnimaDirection();
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
	// �ǈړ��̕�����ǉ����܂�
	void addWSPDirection(const Vector2& direction);
	// �v���C���[�̈ʒu��ݒ肵�܂�
	void setPlayerPosition(const int number, const Vector2& position);
	// �v���C���[�{���I�u�W�F�N�g�̒ǉ����s���܂�
	void setPSObj(const int number, const Vector2 & position);
	// �v���C���[�{���I�u�W�F�N�g�̒ǉ����s���܂�
	PlayerSearchObj* getPSObj(const int number);
	// �������Ă���I�u�W�F�N�g�̍폜���s���܂�
	void deleteObj();

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
	Vector2 threadPosition_;	// ���̈ʒu
	Vector2 enemyDirection_;	// �G�l�~�[�̕���
	Vector2 wsDirection_;		// �ǈړ����̕���
	Vector2 animaDirection_;	// �ǈړ����̃A�j���[�V�����̕���
	IWorld* world_;				// ���[���h
	// �v���C���[���ʗp�R���e�i
	typedef std::map<int, Vector2> PlayerPositionMap;
	PlayerPositionMap positiones_;
	// �v���C���[�{���I�u�W�F�N�g�R���e�i
	typedef std::map<int, PlayerSearchObj*> PSObjMap;
	PSObjMap psObjs;
	// �l�p�`�ړ��p�R���e�i
	typedef std::vector<float> WallMoveConteiner;
	WallMoveConteiner wallMoveConteiner_;
	// �Ǒ{���I�u�W�F�N�g�R���e�i
	typedef std::vector<FloorSearchPoint*> WSPContainer;
	WSPContainer wspContainer_;
	// �f���R���e�i
	typedef std::vector<int> PrimeContainer;
	PrimeContainer primeContainer_;
	// �A�j���[�V���������R���e�i
	// <int, [Vector2, Vector2]>
	typedef std::map<int, Vector2> animaDirectionMap;
	animaDirectionMap animaDirectionMap_;
	// �ǈړ��̕����R���e�i
	typedef std::map<int, Vector2> WSPDirectionMap;
	WSPDirectionMap wspDirectionMap_;
};

#endif