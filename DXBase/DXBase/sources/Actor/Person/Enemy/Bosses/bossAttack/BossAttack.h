#ifndef BOSS_ATTACK_H_
#define BOSS_ATTACK_H_

#include "../../../../../Math/Math.h"
#include "../../../../../Define.h"
#include "../BossAnimationNumber.h"
#include "../../../../../World/IWorld.h"
#include "./../../../../Base/ActorGroup.h"
#include <string>
#include <random>	// C++11�̋@�\

// �{�X�U���N���X(�x�[�X)
class BossAttack {
public:
	BossAttack();
	BossAttack(IWorld* world, const Vector2& position);
	// �f�X�g���N�^
	virtual ~BossAttack();
	// �X�V
	void update(float deltaTime);
	// �U��
	virtual void attack(float deltaTime);
	// �ړ������ʒu���擾���܂�
	Vector2 getMovePosition();
	// �������擾���܂�
	Vector2 getDirection();
	// �U���s���̃��t���b�V�����s���܂�
	virtual void Refresh();
	// �U�����J�n��������Ԃ��܂�
	bool isAttackStart();
	// �U�����I����������Ԃ��܂�
	bool isAttackEnd();

public:
	// �{�X�̐S���̗̑͂�ݒ肵�܂�
	void setHeartHP(const int hp);
	// �ʒu��ݒ肵�܂�
	void setPosition(const Vector2& position);
	// �v���C���[�̈ʒu��ݒ肵�܂�
	void setPlayerPosition(const Vector2& position);
	// �v���C���[�Ƃ̕�����ݒ肵�܂�
	void setPlayerDirection(const Vector2& direction);
	// �v���C���[�Ƃ̐��K�����ꂽ������ݒ肵�܂�
	void setPlayerNormalizeDirection(const Vector2& direction);
	// �Ǒ{���I�u�W�F�N�g��������������ݒ肵�܂�
	void setIsWallHit(bool isHit);
	// �ǈړ��̕������擾���܂�
	Vector2 getMoveDirection();
	// ���ɐG��Ă��邩��ݒ肵�܂�
	void setIsGround(bool isGround);
	// �ǂ̉����ɓ�����������ݒ肵�܂�
	void setIsBottom(bool isBottom);
	// �G��Ă��鏰�̖��O��ݒ肵�܂�
	void setFloorName(const char* name);
	// �U���\��Ԃ���ݒ肵�܂�
	void setIsMove(bool isMove);
	// �Ђ�݃J�E���g��Ԃ��܂�
	int getFlinchCount();
	// �p�x��Ԃ��܂�
	float getAngle();
	// ���ނ���Ԃ��܂�
	bool isFlinch();
	// �d�͂��g�p���邩��Ԃ��܂�
	bool isUseGravity();
	// �v���C���[�̍U���ɓ����邩��Ԃ��܂�
	bool isBodyHit();
	// �v���C���[�ɓ����邩��Ԃ��܂�
	bool isAttackHit();
	// �Փ˂����I�u�W�F�N�g��ݒ肵�܂�
	void setCollideObj(Actor& actor);
	// �A�j���[�V�����ԍ���Ԃ��܂�
	int getAnimaNum();
	// �A�j���[�V�����̊p�x��Ԃ��܂�
	int getAnimeAngle();
	// �A�j���[�V���������[�v���邩��Ԃ��܂�
	bool isLoop();
	// �A�j���[�V�������t�Đ����邩��Ԃ��܂�
	bool isReverse();

protected:
	// �����^�̃����_������Ԃ��܂�
	int getRandomInt(int min, int max);

protected:
	int hp_;					// �̗�
	int flinchCount_;			// �Ђ�ނ܂ł̉�
	float timer_;				// ����
	float angle_;				// �p�x
	float animeAngle_;			// �A�j���[�V�����̊p�x
	std::string floorName_;		// ���̖��O
	bool isAttackStart_;		// �U�����J�n������
	bool isAttackEnd_;			// �U�����I��������
	bool isGround_;				// �{�X�����ɐG��Ă���̂�
	bool isBottom_;				// �ǂ̉����ɓ���������
	bool isUseGravity_;			// �d�͂��g����
	bool isWspHit_;				// �Ǒ{���I�u�W�F�N�g������������
	bool isPrevWspHit_;			// �ߋ��ɕǑ{���I�u�W�F�N�g������������
	bool isBodyHit_;			// �v���C���[�{�̂ɓ����邩
	bool isAttackHit_;			// �v���C���[�̍U���ɓ����邩
	bool isMove_;				// �������Ԃ�
	bool isFlinch_;				// ���ނ�
	bool isAnimaLoop_;			// �A�j���[�V���������[�v�����邩
	bool isAnimaReverse_;		// �A�j���[�V�������t�Đ����邩
	Vector2 position_;			// �ʒu
	Vector2 direction_;			// ����
	Vector2 wsDirection_;		// �Ǒ{���I�u�W�F�N�g�̕���
	Vector2 pPosition_;			// �v���C���[�̈ʒu
	Vector2 pDirection_;		// �v���C���[�Ƃ̕���
	Vector2 pNormDirection_;	// �v���C���[�Ƃ̕���
	IWorld* world_;				// ���[���h�|�C���^
	int animeNum_;				// �A�j���[�V�����ԍ�
	Actor* collideObj_;			// �Փ˂����I�u�W�F�N�g
	std::mt19937 mt_;			// �����̏���seed
};

#endif
