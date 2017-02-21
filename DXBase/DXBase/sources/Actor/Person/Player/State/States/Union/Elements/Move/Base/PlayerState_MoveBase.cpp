#include "PlayerState_MoveBase.h"

#include "../../../../../../../../../Define.h"
#include "../../../../../../../../../Input/InputMgr.h"

// �R���X�g���N�^
PlayerState_MoveBase::PlayerState_MoveBase(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_Union(butty, retty) {}

// ��ԌŗL�̏�����
void PlayerState_MoveBase::unique_init(){
	// butty�̃A�j���[�V������MOVE�ɕύX
	butty_->animation().change(PlayerAnimID::MOVE, 2.0f);
	// retty�̃A�j���[�V������MOVE�ɕύX
	retty_->animation().change(PlayerAnimID::MOVE, 2.0f);

	onInit();
}

void PlayerState_MoveBase::update(float deltaTime){
	// �ړ�����
	move(deltaTime);

	// �{�X�X�e�[�W��p�C�x���g����Event��ԂɕύX
	if (cntr_->getWorld()->isEntered()) change(PlayerState_Enum_Union::EVENT);

	onUpdate(deltaTime);
}

void PlayerState_MoveBase::end(){
	onEnd();
}

void PlayerState_MoveBase::key_input(float deltaTime){
	onKeyInput(deltaTime);
}

void PlayerState_MoveBase::pad_input(float deltaTime){
	onPadInput(deltaTime);
}

void PlayerState_MoveBase::move(float deltaTime)
{
}

void PlayerState_MoveBase::flip_animation()
{
}
