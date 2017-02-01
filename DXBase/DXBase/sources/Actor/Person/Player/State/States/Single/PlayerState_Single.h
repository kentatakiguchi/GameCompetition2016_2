#pragma once

#include "../../Base/IState.h"

#include "../../PlayerState_Enum.h"

#include "../../../PlayerPtr.h"
#include "../../../Player.h"
#include "../../../PlayerBody.h"

// �e�v���C���[�X�e�[�g�̊��N���X
class PlayerState_Single : public IState {
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
	virtual void common_init(Actor& actor, const ActionType& type) override;
	// ���͏���
	virtual void input(float deltaTime) override;
	// ���͏���
	virtual void common_update(float deltaTime) override;
	// �Փˏ���
	virtual void collide(const Actor & other) override;
	// �`�揈��
	virtual void draw()const override;
	// �X�e�[�g�̕ύX����
	virtual void change(const StateElement& element) override;
	// �X�e�[�g���I���������ۂ�
	virtual bool isEnd() override;
	// ���̃X�e�[�g�̗v�f
	virtual StateElement next() const override;
protected:
	bool is_butty();
	bool is_retty();
private:
	// �L�[���͏���
	virtual void key_input(float deltaTime);
	// �p�b�h���͏���
	virtual void pad_input(float deltaTime);
protected:
	// �X�e�[�g�̗v�f
	StateElement element_;
	// �X�e�[�g�̗v�f
	StateElement next_element_;
	// �X�e�[�g���I���������ۂ�
	bool isEnd_;
	// �^�C�}�[
	float timer_;
	// �v���C���[�|�C���^
	PlayerBody* body_;
	// �L�[
	Keys keys_;
};