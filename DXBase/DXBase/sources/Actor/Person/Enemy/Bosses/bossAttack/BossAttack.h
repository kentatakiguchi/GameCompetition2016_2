#ifndef BOSS_ATTACK_H_
#define BOSS_ATTACK_H_

#include "../../../../../Math/Math.h"
#include "../../../../../Define.h"
#include <string>

// �{�X�U���N���X(�x�[�X)
class BossAttack {
public:
	BossAttack();
	BossAttack(const Vector2& position);
	// �f�X�g���N�^
	virtual ~BossAttack();
	// �X�V
	void update(float deltaTime);
	// �U��
	virtual void attack(float deltaTime);
	// �ړ������ʒu���擾���܂�
	Vector2 getMovePosition();
	// �U���s���̃��t���b�V�����s���܂�
	virtual void Refresh();
	// �U�����J�n��������Ԃ��܂�
	bool isAttackStart();
	// �U�����I����������Ԃ��܂�
	bool isAttackEnd();

public:
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
	//void setDirection(const Vector2& direction);
	// �ǈړ��̕������擾���܂�
	Vector2 getMoveDirection();
	// ���ɐG��Ă��邩��ݒ肵�܂�
	void setIsGround(bool isGround);
	// �ǂ̉����ɓ�����������ݒ肵�܂�
	void setIsBottom(bool isBottom);
	// �G��Ă��鏰�̖��O��ݒ肵�܂�
	void setFloorName(const char* name);
	// �d�͂��g�p���邩��Ԃ��܂�
	bool IsUseGravity();
	// �v���C���[�̍U���ɓ����邩��Ԃ��܂�
	bool IsBodyHit();
	// �v���C���[�ɓ����邩��Ԃ��܂�
	bool IsAttackHit();

protected:
	float timer_;				// ����
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
	Vector2 position_;			// �ʒu
	Vector2 direction_;			// ����
	Vector2 pPosition_;			// �v���C���[�̈ʒu
	Vector2 pDirection_;		// �v���C���[�Ƃ̕���
	Vector2 pNormDirection_;	// �v���C���[�Ƃ̕���
};

#endif
