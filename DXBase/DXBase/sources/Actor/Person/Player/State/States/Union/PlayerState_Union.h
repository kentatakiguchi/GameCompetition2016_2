#pragma once

#include "../../Base/State.h"

#include "../../PlayerState_Enum.h"

#include "../../../PlayerPtr.h"
#include "../../../Player.h"
#include "../../../PlayerConnector.h"
#include "../../../PlayerBody.h"

// �e�v���C���[�X�e�[�g�̊��N���X
class PlayerState_Union : public State {
public:
	// �R���X�g���N�^
	PlayerState_Union(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
	// �S�ẴX�e�[�g�ɋ��ʂ��鏉��������
	virtual void common_init(Actor& actor, const StateElement& element) override;
	// ���͏���
	virtual void input(float deltaTime) override;
	// ���͏���
	virtual void common_update(float deltaTime) override;
	// �Փˏ���
	virtual void collide(const Actor & other) override;
	// �`�揈��
	virtual void draw()const override;
protected:
	// �X�e�[�g�̕ύX����
	void change(const PlayerState_Enum_Union& id, const ActionType& type = ActionType::None);
protected:
	// �p�b�h�n�t���O
	bool holdable_padR();
	bool holdable_padL();
	bool move_padR();
	bool move_padL();
	bool jump_pad();
	// �X���C���̒e���\��
	Vector2 speed_b(float deltaTime);
	Vector2 speed_r(float deltaTime);
	void chase(Vector2 &position, int pointIndex);
	Vector2 clamp(const Vector2 &position, int pointIndex);

	bool isOnFloor();
protected:
	// �΂˕␳���x
	Vector2 velocity_;
	// �v���C���[�|�C���^
	PlayerConnector* cntr_;
	// �v���C���[�|�C���^
	PlayerBodyPtr butty_;
	// �v���C���[�|�C���^
	PlayerBodyPtr retty_;
};