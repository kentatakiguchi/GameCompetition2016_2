#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"

#include "PlayerPtr.h"

// �v���[���[
class Player : public Actor {
public:
	// �R���X�g���N�^
	Player(IWorld* world, const Vector2& position);
	// �f�X�g���N�^
	~Player();
	// �X�V����
	virtual void onUpdate(float deltaTime) override;
	void setClampPoint(Vector2 point);
private:
	// body���S���W
	Vector2 center();
	// body����
	void create_bodys();
	// �w��state�̍X�V����
	void update_state(float deltaTime);
	// �ڑ�����
	void connect();
	// �ڑ��\���ǂ���
	bool is_connectable();
	// ���S�������ǂ���
	bool is_dead();
private:
	// body(��)
	PlayerBodyPtr butty_;
	// body(��)
	PlayerBodyPtr retty_;
	Vector2 prePos_;
};

