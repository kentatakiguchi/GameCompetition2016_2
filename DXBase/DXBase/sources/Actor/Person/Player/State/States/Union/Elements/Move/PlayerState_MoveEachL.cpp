#include "PlayerState_MoveEachL.h"

#include "../../../../../../../../Define.h"
#include "../../../../../../../../Input/InputMgr.h"

PlayerState_MoveEachL::PlayerState_MoveEachL(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) :PlayerState_MoveBase(butty, retty) {}

void PlayerState_MoveEachL::onInit(){
}

void PlayerState_MoveEachL::onUpdate(float deltaTime){

	// �d�͂̌v�Z
	Vector2 gravity = Vector2::Up * GRAVITY * deltaTime * static_cast<float>(GetRefreshRate());;
	// butty�ɏd�͂��|����
	butty_->position() += gravity * butty_->velocity();
	// retty�ɏd�͂��|����
	retty_->position() += gravity * retty_->velocity();

	// retty�̒ǐՌv�Z
	chase(butty_->position(), 0);

	// butty�̈ړ�����
	butty_->position() = clamp(butty_->position(), 0);
	// retty�̈ړ�����
	retty_->position() = clamp(retty_->position(), PLAYER_CNTR_DIV_NUM - 1);

	if (butty_->getPosition().x > retty_->getPosition().x) {
		butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);
	}
	else {
		butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	}
}

void PlayerState_MoveEachL::onEnd(){}

void PlayerState_MoveEachL::onKeyInput(float deltaTime){
	// retty�̓��͂ɂ�锽�]����
	if (InputMgr::GetInstance().KeyVector_L().x > 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().KeyVector_L().x < 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	// ���͂ɂ��ړ�����
	retty_->position() += InputMgr::GetInstance().KeyVector_L().Horizontal() * speed_r(deltaTime);

	// �W�����v����
	if (jump_key()) change(PlayerState_Enum_Union::JUMP);
	// �ړ����͂��Ȃ��ꍇIDLE�ɕύX
	else if (!move_keyR() && !move_keyL()) change(PlayerState_Enum_Union::IDLE);
	// ���ړ��L�[�����͂��ꂽ�ꍇ��Ԃ�MOVE_BOTH�ɕύX
	else if (move_keyR()) change(PlayerState_Enum_Union::MOVE_BOTH);
	else if (holdable_keyR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	else if (holdable_keyL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);

}

void PlayerState_MoveEachL::onPadInput(float deltaTime){

	// retty�̓��͂ɂ�锽�]����
	if (InputMgr::GetInstance().AnalogPadVectorL().x > 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().AnalogPadVectorL().x < 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	// ���͂ɂ��ړ�����
	retty_->position() += InputMgr::GetInstance().AnalogPadVectorL().Horizontal() * speed_r(deltaTime);

	// �W�����v����
	if (jump_pad()) change(PlayerState_Enum_Union::JUMP);
	// �ړ����͂��Ȃ��ꍇIDLE�ɕύX
	else if (!move_padR() && !move_padL()) change(PlayerState_Enum_Union::IDLE);
	// ���ړ��X�e�B�b�N�����͂��ꂽ�ꍇ��Ԃ�MOVE_BOTH�ɕύX
	else if (move_padR()) change(PlayerState_Enum_Union::MOVE_BOTH);
	else if (holdable_padR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	else if (holdable_padL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
}
