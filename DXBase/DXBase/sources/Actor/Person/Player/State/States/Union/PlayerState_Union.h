#pragma once

#include "../../Base/IState.h"

#include "../../PlayerState_Enum.h"

#include "../../../PlayerPtr.h"
#include "../../../Player.h"
#include "../../../PlayerConnector.h"
#include "../../../PlayerBody.h"

// �e�v���C���[�X�e�[�g�̊��N���X
class PlayerState_Union : public IState {
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
	// �X�e�[�g���I���������ۂ�
	virtual bool isEnd() override;
	// ���̃X�e�[�g�̗v�f
	virtual StateElement next() const override;
private:
	// �X�e�[�g�̕ύX����
	virtual void change(const StateElement& element) override;
protected:
	// �X�e�[�g�̕ύX����
	void change(const PlayerState_Enum_Union& id, const ActionType& type = ActionType::None);
protected:
	// �L�[�n�t���O
	bool holdable_keyR();
	bool holdable_keyL();
	bool move_keyR();
	bool move_keyL();
	bool jump_key();
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

	// �d��
	Vector2 gravity(float deltaTime) const;
protected:
	// �X�e�[�g�̗v�f
	StateElement element_;
	// �X�e�[�g�̗v�f
	StateElement next_element_;
	// �X�e�[�g���I���������ۂ�
	bool isEnd_;
	// �^�C�}�[
	float timer_;
	// �΂˕␳���x
	Vector2 velocity_;
	// �v���C���[�|�C���^
	PlayerConnector* cntr_;
	// �v���C���[�|�C���^
	PlayerBodyPtr butty_;
	// �v���C���[�|�C���^
	PlayerBodyPtr retty_;
};