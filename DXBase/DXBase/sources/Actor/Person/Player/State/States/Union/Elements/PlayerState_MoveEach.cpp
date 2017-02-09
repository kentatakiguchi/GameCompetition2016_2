#include "PlayerState_MoveEach.h"

#include "../../../../../../../Define.h"
#include "../../../../../../../Input/InputMgr.h"

// コンストラクタ
PlayerState_MoveEach::PlayerState_MoveEach(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty) : PlayerState_Union(butty, retty) {}

// 状態固有の初期化
void PlayerState_MoveEach::unique_init(){
	// buttyのアニメーションをMOVEに変更
	butty_->animation().change(PlayerAnimID::MOVE, 2.0f);
	// rettyのアニメーションをMOVEに変更
	retty_->animation().change(PlayerAnimID::MOVE, 2.0f);
}

// 更新処理
void PlayerState_MoveEach::update(float deltaTime){
	// アニメーション反転
	flip_animation();

	// 移動処理
	move(deltaTime);

	// ボスステージ専用イベント時にEvent状態に変更
	if (cntr_->getWorld()->isEntered()) change(PlayerState_Enum_Union::EVENT);
}

// 終了時処理
void PlayerState_MoveEach::end(){}

// キー入力処理
void PlayerState_MoveEach::key_input(float deltaTime){
	// buttyの入力による反転処理
	if (InputMgr::GetInstance().KeyVector_R().x > 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().KeyVector_R().x < 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	// rettyの入力による反転処理
	if (InputMgr::GetInstance().KeyVector_L().x > 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().KeyVector_L().x < 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	// 入力による移動処理
	if (element_.type_ == ActionType::Right) butty_->position() += InputMgr::GetInstance().KeyVector_R().Horizontal() * speed_b(deltaTime);
	if (element_.type_ == ActionType::Left)  retty_->position() += InputMgr::GetInstance().KeyVector_L().Horizontal() * speed_r(deltaTime);

	// ジャンプ処理
	if (jump_key()) change(PlayerState_Enum_Union::JUMP);
	// 移動入力がない場合IDLEに変更
	else if (!move_keyR() && !move_keyL()) change(PlayerState_Enum_Union::IDLE);
	// 両移動キーが入力された場合状態をMOVE_BOTHに変更
	else if (element_.type_ == ActionType::Right && move_keyL()) change(PlayerState_Enum_Union::MOVE_BOTH);
	else if (element_.type_ == ActionType::Left  && move_keyR()) change(PlayerState_Enum_Union::MOVE_BOTH);
	else if (holdable_keyR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	else if (holdable_keyL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
}

// パッド入力処理
void PlayerState_MoveEach::pad_input(float deltaTime){
	// buttyの入力による反転処理
	if (InputMgr::GetInstance().AnalogPadVectorR().x > 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().AnalogPadVectorR().x < 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	// rettyの入力による反転処理
	if (InputMgr::GetInstance().AnalogPadVectorL().x > 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().AnalogPadVectorL().x < 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	// 入力による移動処理
	if (element_.type_ == ActionType::Right) butty_->position() += InputMgr::GetInstance().AnalogPadVectorR().Horizontal() * speed_b(deltaTime);
	if (element_.type_ == ActionType::Left)  retty_->position() += InputMgr::GetInstance().AnalogPadVectorL().Horizontal() * speed_r(deltaTime);
	
	// ジャンプ処理
	if (jump_pad()) change(PlayerState_Enum_Union::JUMP);
	// 移動入力がない場合IDLEに変更
	else if (!move_padR() && !move_padL()) change(PlayerState_Enum_Union::IDLE);
	// 両移動スティックが入力された場合状態をMOVE_BOTHに変更
	else if (element_.type_ == ActionType::Right && move_padL()) change(PlayerState_Enum_Union::MOVE_BOTH);
	else if (element_.type_ == ActionType::Left  && move_padR()) change(PlayerState_Enum_Union::MOVE_BOTH);
	else if (holdable_padR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	else if (holdable_padL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
}

// 移動処理
void PlayerState_MoveEach::move(float deltaTime) {
	// 重力の計算
	Vector2 gravity = Vector2::Up * GRAVITY * deltaTime * static_cast<float>(GetRefreshRate());;
	// buttyに重力を掛ける
	butty_->position() += gravity * butty_->velocity();
	// rettyに重力を掛ける
	retty_->position() += gravity * retty_->velocity();

	// buttyの追跡計算
	if (element_.type_ == ActionType::Right) chase(retty_->position(), PLAYER_CNTR_DIV_NUM - 1);
	// rettyの追跡計算
	if (element_.type_ == ActionType::Left)  chase(butty_->position(), 0);
	
	// buttyの移動制限
	butty_->position() = clamp(butty_->position(), 0);
	// rettyの移動制限
	retty_->position() = clamp(retty_->position(), PLAYER_CNTR_DIV_NUM - 1);
}

void PlayerState_MoveEach::flip_animation(){
	if (element_.type_ == ActionType::Right) {
		if (butty_->getPosition().x > retty_->getPosition().x) {
			retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
		}
		else {
			retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);
		}
	}
	if (element_.type_ == ActionType::Left) {
		if (butty_->getPosition().x > retty_->getPosition().x) {
			butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);
		}
		else {
			butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
		}
	}
}

