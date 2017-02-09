#include "PlayerState_Idle.h"

// コンストラクタ
PlayerState_Idle::PlayerState_Idle(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty) : PlayerState_Union(butty, retty) {
}

// 状態固有の初期化
void PlayerState_Idle::unique_init(){
	// buttyのアニメーションをIDLEに変更
	butty_->animation().change(PlayerAnimID::IDLE);
	// rettyのアニメーションをIDLEに変更
	retty_->animation().change(PlayerAnimID::IDLE);

	//cntr_->getWorld()->GetKeeper()->setJumpCount(0);
}

// 更新処理
void PlayerState_Idle::update(float deltaTime) {
	// 移動処理
	move(deltaTime);

	// ボスステージ専用イベント時にEvent状態に変更
	if (cntr_->getWorld()->isEntered()) change(PlayerState_Enum_Union::EVENT);
}

// 終了時処理
void PlayerState_Idle::end(){}

// キー入力処理
void PlayerState_Idle::key_input(float deltaTime){
	// ジャンプキー入力時にジャンプ状態に変更
	if (jump_key()) change(PlayerState_Enum_Union::JUMP);

	// butty移動キー入力時にbutty移動状態に変更
	else if (move_keyR()) change(PlayerState_Enum_Union::MOVE, ActionType::Right);
	// retty移動キー入力時にretty移動状態に変更
	else if (move_keyL()) change(PlayerState_Enum_Union::MOVE, ActionType::Left );

	// buttyくっつき可能時に右シフトキーでくっつき状態に変更
	else if (holdable_keyR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	// rettyくっつき可能時に左シフトキーでくっつき状態に変更
	else if (holdable_keyL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
}

// パッド入力処理
void PlayerState_Idle::pad_input(float deltaTime){
	// ジャンプボタン入力時にジャンプ状態に変更
	if (jump_pad()) change(PlayerState_Enum_Union::JUMP);

	// 右スティック入力時にbutty移動状態に変更
	else if (move_padR()) change(PlayerState_Enum_Union::MOVE, ActionType::Right);
	// 左スティック入力時にbutty移動状態に変更
	else if (move_padL()) change(PlayerState_Enum_Union::MOVE, ActionType::Left);

	// buttyくっつき可能時にR1ボタンでくっつき状態に変更
	else if (holdable_padR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	// rettyくっつき可能時にR1ボタンでくっつき状態に変更
	else if (holdable_padL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
}

// 移動処理
void PlayerState_Idle::move(float deltaTime) {
	// 重力の計算
	Vector2 gravity = Vector2::Up * GRAVITY * deltaTime * static_cast<float>(GetRefreshRate());
	// buttyに重力を掛ける
	butty_->position() += gravity * butty_->velocity();
	// rettyに重力を掛ける
	retty_->position() += gravity * retty_->velocity();

	// buttyの追跡計算
	chase(butty_->position(), 0);
	// rettyの追跡計算
	chase(retty_->position(), PLAYER_CNTR_DIV_NUM - 1);

	// buttyの移動制限
	butty_->position() = clamp(butty_->position(), 0);
	// rettyの移動制限
	retty_->position() = clamp(retty_->position(), PLAYER_CNTR_DIV_NUM - 1);
}



