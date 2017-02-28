#pragma once

#include "../../Base/State.h"

#include "../../../PlayerBody.h"

#include "../../../../../../Input/KeyCode.h"

// �e�v���C���[�X�e�[�g�̊��N���X
class PlayerState_Single : public State {
public:
	struct Keys {
	public:
		KeyCode up;
		KeyCode down;
		KeyCode right;
		KeyCode left;
	public:
		Keys(const KeyCode& up = KeyCode::UP, const KeyCode& down = KeyCode::DOWN, const KeyCode& right = KeyCode::RIGHT, const KeyCode& left = KeyCode::LEFT) :up(up), down(down), right(right), left(left) {}
	};
public:
	// �R���X�g���N�^
	PlayerState_Single(const Keys& keys);
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
	bool is_butty() const;
	bool is_retty() const;
protected:
	// �v���C���[�|�C���^
	PlayerBody* body_;
	// �L�[
	Keys keys_;
};