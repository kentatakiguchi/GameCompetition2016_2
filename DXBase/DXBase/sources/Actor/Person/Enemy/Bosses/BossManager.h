#ifndef BOSS_MANAGER_H_
#define BOSS_MANAGER_H_

#include "bossAttack/BossAttack.h"
#include <vector>
#include <memory>

class IWorld;

// �{�X�}�l�[�W���[ 
class BossManager {
public:
	BossManager();
	// �R���X�g���N�^
	BossManager(IWorld* world, const Vector2& position);
	// �f�X�g���N�^
	~BossManager();
	// �U���R���e�i�ɍU����ǉ����܂�
	void addAttack(std::shared_ptr<BossAttack> attack);
	// �U���̔ԍ���ύX���܂�
	void changeAttackNumber(const int number);
	// �w�肵���ԍ��̍U���s�����s���܂�
	void attackMove(const float deltaTime);
	// �U���̃��t���b�V�����s���܂�
	void attackRefresh();
	// �s���ɂ���Ĉړ������ʒu��Ԃ��܂�
	Vector2 getMovePosition();
	// �U���������擾���܂�
	Vector2 getAttackDirection();
	// �U�����J�n��������Ԃ��܂�
	bool isAttackStart();
	// �U�����I����������Ԃ��܂�
	bool isAttackEnd();
	// �v���C���[�̍U���ɓ����邩��Ԃ��܂�
	bool IsBodyHit();
	// �v���C���[�ɓ����邩��Ԃ��܂�
	bool IsAttackHit();
	// ���ނ���Ԃ��܂�
	bool isFlinch();
	// �Ђ�݃J�E���g��Ԃ��܂�
	int getFlinchCount();
	// �p�x��Ԃ��܂�
	float getAngle();

public:
	// �{�X�̐S���̗̑͂�ݒ肵�܂�
	void setHeartHP(const int hp);
	// �{�X�̈ʒu��ݒ肵�܂�
	void setPosition(const Vector2& position);
	// �v���C���[�̈ʒu��ݒ肵�܂�
	void setPlayerPosition(const Vector2& position);
	// �U���O�̈ʒu�����肵�܂�
	void prevPosition();
	// �w�肵���I�u�W�F�N�g�Ƃ̕�����P�ʃx�N�g���Ŏ擾���܂�
	Vector2 getDirection(const Vector2& otherPosition);
	// �v���C���[�Ƃ̕�����P�ʃx�N�g���Ŏ擾���܂�
	Vector2 getPlayerDirection();
	// �w�肵���I�u�W�F�N�g�Ƃ̕����𐳋K���x�N�g���Ŏ擾���܂�
	Vector2 getNormalizeDirection(const Vector2& otherPosition);
	// �v���C���[�Ƃ̕����𐳋K���x�N�g���Ŏ擾���܂�
	Vector2 getPlayerNormalizeDirection();
	// �{�X���ڒn���Ă��邩��ݒ肵�܂�
	void setIsGround(bool isGround);
	// �{�X���ǂ̉����ɓ�����������ݒ肵�܂�
	void setIsBottom(bool isBottom);
	// �{�X�������������̖��O��Ԃ��܂�
	void setFloorName(const char* name);
	// �U�����ɏd�͂��g�p���邩��Ԃ��܂�
	bool isUseGravity();
	// �U�����\�ȏ�Ԃ���ݒ肵�܂�
	void setIsAttackMove(bool isMove);
	// �Ǒ{���I�u�W�F�N�g��������������ݒ肵�܂�
	void setIsWallHit(bool isHit);
	// �ǂ̈ړ�����
	Vector2 getWallMoveDirection();
	// �Փ˂����I�u�W�F�N�g��ݒ肵�܂�
	void setCollideObj(Actor& actor);
	// �A�j���[�V�����ԍ���Ԃ��܂�
	//BossAnimationNumber getAnimaNum();
	int getAnimaNum();
	// �A�j���[�V�����̊p�x��Ԃ��܂�
	int getAnimeAngle();
	// �A�j���[�V���������[�v���邩��Ԃ��܂�
	bool isAnimeLoop();
	// �A�j���[�V�������t�Đ����邩��Ԃ��܂�
	bool isAnimeReverse();

private:
	int attackNumber_;			// �U���ԍ�
	Vector2 bossPosition_;		// �{�X�̈ʒu
	Vector2 playerPosition_;	// �v���C���[�̈ʒu
	// �{�X�U���R���e�i
	typedef std::vector<std::shared_ptr<BossAttack>> BossAttackContainer;
	BossAttackContainer bossAttackContainer_;
};

#endif
