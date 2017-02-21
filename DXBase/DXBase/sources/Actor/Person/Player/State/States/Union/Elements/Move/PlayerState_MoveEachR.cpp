#include "PlayerState_MoveEachR.h"

#include "../../../../../../../../Define.h"
#include "../../../../../../../../Input/InputMgr.h"

PlayerState_MoveEachR::PlayerState_MoveEachR(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty):PlayerState_MoveBase(butty, retty){}

void PlayerState_MoveEachR::onInit(){
}

void PlayerState_MoveEachR::onUpdate(float deltaTime)
{
	// �d�͂̌v�Z
	Vector2 gravity = Vector2::Up * GRAVITY * deltaTime * static_cast<float>(GetRefreshRate());;
	// butty�ɏd�͂��|����
	butty_->position() += gravity * butty_->velocity();
	// retty�ɏd�͂��|����
	retty_->position() += gravity * retty_->velocity();

	// butty�̒ǐՌv�Z
	/*if (element_.type_ == ActionType::Right) */chase(retty_->position(), PLAYER_CNTR_DIV_NUM - 1);
	//// retty�̒ǐՌv�Z
	//if (element_.type_ == ActionType::Left)  chase(butty_->position(), 0);

	// butty�̈ړ�����
	butty_->position() = clamp(butty_->position(), 0);
	// retty�̈ړ�����
	retty_->position() = clamp(retty_->position(), PLAYER_CNTR_DIV_NUM - 1);


	if (butty_->getPosition().x > retty_->getPosition().x) {
		retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	}
	else {
		retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);
	}
}

void PlayerState_MoveEachR::onEnd()
{
}

void PlayerState_MoveEachR::onKeyInput(float deltaTime){
	// butty�̓��͂ɂ�锽�]����
	if (InputMgr::GetInstance().KeyVector_R().x > 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().KeyVector_R().x < 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	// ���͂ɂ��ړ�����
	butty_->position() += InputMgr::GetInstance().KeyVector_R().Horizontal() * speed_b(deltaTime);

	// �W�����v����
	if (jump_key()) change(PlayerState_Enum_Union::JUMP);
	// �ړ����͂��Ȃ��ꍇIDLE�ɕύX
	else if (!move_keyR() && !move_keyL()) change(PlayerState_Enum_Union::IDLE);
	// ���ړ��L�[�����͂��ꂽ�ꍇ��Ԃ�MOVE_BOTH�ɕύX
	else if (element_.type_ == ActionType::Right && move_keyL()) change(PlayerState_Enum_Union::MOVE_BOTH);
	else if (holdable_keyR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	else if (holdable_keyL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);

}

void PlayerState_MoveEachR::onPadInput(float deltaTime){
	// butty�̓��͂ɂ�锽�]����
	if (InputMgr::GetInstance().AnalogPadVectorR().x > 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().AnalogPadVectorR().x < 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	// ���͂ɂ��ړ�����
	butty_->position() += InputMgr::GetInstance().AnalogPadVectorR().Horizontal() * speed_b(deltaTime);

	// �W�����v����
	if (jump_pad()) change(PlayerState_Enum_Union::JUMP);
	// �ړ����͂��Ȃ��ꍇIDLE�ɕύX
	else if (!move_padR() && !move_padL()) change(PlayerState_Enum_Union::IDLE);
	// ���ړ��X�e�B�b�N�����͂��ꂽ�ꍇ��Ԃ�MOVE_BOTH�ɕύX
	else if (element_.type_ == ActionType::Right && move_padL()) change(PlayerState_Enum_Union::MOVE_BOTH);
	else if (holdable_padR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	else if (holdable_padL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);

}
