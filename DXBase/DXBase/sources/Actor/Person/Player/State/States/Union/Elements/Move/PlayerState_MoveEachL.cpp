#include "PlayerState_MoveEachL.h"

#include "../../../../../../../../Define.h"
#include "../../../../../../../../Input/InputMgr.h"

PlayerState_MoveEachL::PlayerState_MoveEachL(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) :PlayerState_MoveBase(butty, retty) {}

void PlayerState_MoveEachL::onInit(){
}

void PlayerState_MoveEachL::onUpdate(float deltaTime){

	// 重力の計算
	Vector2 gravity = Vector2::Up * GRAVITY * deltaTime * static_cast<float>(GetRefreshRate());;
	// buttyに重力を掛ける
	butty_->position() += gravity * butty_->velocity();
	// rettyに重力を掛ける
	retty_->position() += gravity * retty_->velocity();

	// rettyの追跡計算
	chase(butty_->position(), 0);

	// buttyの移動制限
	butty_->position() = clamp(butty_->position(), 0);
	// rettyの移動制限
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
	// rettyの入力による反転処理
	if (InputMgr::GetInstance().KeyVector_L().x > 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().KeyVector_L().x < 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	// 入力による移動処理
	retty_->position() += InputMgr::GetInstance().KeyVector_L().Horizontal() * speed_r(deltaTime);

	// ジャンプ処理
	if (jump_key()) change(PlayerState_Enum_Union::JUMP);
	// 移動入力がない場合IDLEに変更
	else if (!move_keyR() && !move_keyL()) change(PlayerState_Enum_Union::IDLE);
	// 両移動キーが入力された場合状態をMOVE_BOTHに変更
	else if (move_keyR()) change(PlayerState_Enum_Union::MOVE_BOTH);
	else if (holdable_keyR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	else if (holdable_keyL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);

}

void PlayerState_MoveEachL::onPadInput(float deltaTime){

	// rettyの入力による反転処理
	if (InputMgr::GetInstance().AnalogPadVectorL().x > 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().AnalogPadVectorL().x < 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	// 入力による移動処理
	retty_->position() += InputMgr::GetInstance().AnalogPadVectorL().Horizontal() * speed_r(deltaTime);

	// ジャンプ処理
	if (jump_pad()) change(PlayerState_Enum_Union::JUMP);
	// 移動入力がない場合IDLEに変更
	else if (!move_padR() && !move_padL()) change(PlayerState_Enum_Union::IDLE);
	// 両移動スティックが入力された場合状態をMOVE_BOTHに変更
	else if (move_padR()) change(PlayerState_Enum_Union::MOVE_BOTH);
	else if (holdable_padR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	else if (holdable_padL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
}
