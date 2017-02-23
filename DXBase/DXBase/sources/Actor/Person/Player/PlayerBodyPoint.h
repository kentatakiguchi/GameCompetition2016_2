#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"

// �v���[���[�A���pBody
class PlayerBodyPoint : public Actor {
public:
	// �R���X�g���N�^
	PlayerBodyPoint(IWorld* world, const Vector2 & position, const int& index);
	// �f�X�g���N�^
	~PlayerBodyPoint();
	// �X�V����
	virtual void onUpdate(float deltaTime) override;
	// �`�揈��
	virtual void onDraw() const override;
	// �Փˏ���
	virtual void onCollide(Actor& other) override;
	// ���͍X�V����
	void attract_update(float deltaTime);
	// ���͍X�V����
	void clamp_update(int index);
private:
	// ���g��index�ԍ�
	int index_;
	// �o�l��ԑ��x
	Vector2 v1_, v2_;
	// �e�X�g�p�o�l�n�ϐ�
	float stiffness_;
	float friction_;
	float mass_;

	Vector2 pre_;
};
