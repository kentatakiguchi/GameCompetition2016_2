#include "PlayerState_MoveBoth.h"

#include "../../../../../../../Define.h"
#include "../../../../../../../Input/InputMgr.h"

// �R���X�g���N�^
PlayerState_MoveBoth::PlayerState_MoveBoth(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty) : PlayerState_Union(butty, retty) {}

// ��ԌŗL�̏�����
void PlayerState_MoveBoth::unique_init(){}

// �X�V����
void PlayerState_MoveBoth::update(float deltaTime){
	// �ړ�����
	move(deltaTime);

	// �{�X�X�e�[�W��p�C�x���g����Event��ԂɕύX
	if (cntr_->getWorld()->isEntered()) change(PlayerState_Enum_Union::EVENT);
}

// �I��������
void PlayerState_MoveBoth::end(){}

// �L�[���͏���
void PlayerState_MoveBoth::key_input(float deltaTime){
	// butty�̓��͂ɂ�锽�]����
	if (InputMgr::GetInstance().KeyVector_R().x > 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().KeyVector_R().x < 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	// retty�̓��͂ɂ�锽�]����
	if (InputMgr::GetInstance().KeyVector_L().x > 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().KeyVector_L().x < 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);
	
	// ���͂ɂ��ړ�����
	butty_->position() += InputMgr::GetInstance().KeyVector_R().Horizontal() * speed_b(deltaTime);
	retty_->position() += InputMgr::GetInstance().KeyVector_L().Horizontal() * speed_r(deltaTime);

	// �W�����v����
	if (jump_key()) change(PlayerState_Enum_Union::JUMP);
	// �Е��̓��͂��Ȃ��ꍇMOVE�ɕύX
	else if (!move_keyR()) change(PlayerState_Enum_Union::MOVE, ActionType::Left);
	else if (!move_keyL()) change(PlayerState_Enum_Union::MOVE, ActionType::Right);
	else if (holdable_keyR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	else if (holdable_keyL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
}

// �p�b�h���͏���
void PlayerState_MoveBoth::pad_input(float deltaTime) {
	// butty�̓��͂ɂ�锽�]����
	if (InputMgr::GetInstance().AnalogPadVectorR().x > 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().AnalogPadVectorR().x < 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	// retty�̓��͂ɂ�锽�]����
	if (InputMgr::GetInstance().AnalogPadVectorL().x > 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().AnalogPadVectorL().x < 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	// ���͂ɂ��ړ�����
	butty_->position() += InputMgr::GetInstance().AnalogPadVectorR().Horizontal() * speed_b(deltaTime);
	retty_->position() += InputMgr::GetInstance().AnalogPadVectorL().Horizontal() * speed_r(deltaTime);

	// �W�����v����
	if (jump_pad()) change(PlayerState_Enum_Union::JUMP);
	// �Е��̓��͂��Ȃ��ꍇMOVE�ɕύX
	else if (!move_padR()) change(PlayerState_Enum_Union::MOVE, ActionType::Left);
	else if (!move_padL()) change(PlayerState_Enum_Union::MOVE, ActionType::Right);
	else if (holdable_padR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	else if (holdable_padL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);

}

// �ړ�����
void PlayerState_MoveBoth::move(float deltaTime){
	// �d�͂̌v�Z
	Vector2 gravity = Vector2::Up * GRAVITY * deltaTime * static_cast<float>(GetRefreshRate());
	// butty�ɏd�͂��|����
	butty_->position() += gravity * butty_->velocity();
	// retty�ɏd�͂��|����
	retty_->position() += gravity * retty_->velocity();
	// butty�̈ړ�����
	butty_->position() = clamp(butty_->position(), 0);
	// retty�̈ړ�����
	retty_->position() = clamp(retty_->position(), PLAYER_CNTR_DIV_NUM - 1);
}
