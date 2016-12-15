#pragma once

#include "../../../Base/Actor.h"
#include "../../../../World/IWorld.h"
#include "../../../../Animation/Player/PlayerEffect2D.h"
//#include "EventMessage.h"

// �v���[���[�G�t�F�N�g�I�u�W�F
class PlayerEffectObj : public Actor {
public:
	// �R���X�g���N�^
	PlayerEffectObj(IWorld* world, const Vector2& position, const PlayerEffectID & id, const float& speed = 1.0f, const float& scale = 1.0f);
	// �f�X�g���N�^
	~PlayerEffectObj();
	// �X�V����
	virtual void onUpdate(float deltaTime) override;
	// �`�揈��
	virtual void onDraw() const override;
private:
	// �G�t�F�N�g�N���X
	PlayerEffect2D effect_;
	// �g�嗦
	float scale_;
};