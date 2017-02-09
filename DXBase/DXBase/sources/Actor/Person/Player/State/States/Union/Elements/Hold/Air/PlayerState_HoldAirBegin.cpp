#include "PlayerState_HoldAirBegin.h"

#include "../../../../../../../../../Input/InputMgr.h"

#include "../../../../../../../../../Define.h"

// コンストラクタ
PlayerState_HoldAirBegin::PlayerState_HoldAirBegin(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_HoldBase(butty, retty) {}

// 状態固有の初期化
void PlayerState_HoldAirBegin::onInit() {
	// アニメーションの変更
	if (element_.type_ == ActionType::Right) {
		butty_->animation().change(PlayerAnimID::HOLD);
		retty_->animation().change(PlayerAnimID::SWIM);
	}
	if (element_.type_ == ActionType::Left) {
		retty_->animation().change(PlayerAnimID::HOLD);
		butty_->animation().change(PlayerAnimID::SWIM);
	}

	// くっつき時効果音再生
	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_SYOUTOTU), DX_PLAYTYPE_BACK);

}

// 更新処理	
void PlayerState_HoldAirBegin::onUpdate(float deltaTime) {
	// プレイヤーが一定距離離れたらHOLD_SWIM状態に遷移
	if (retty_->distance() >= PLAYER_SWIM_LENGTH) {
		change(PlayerState_Enum_Union::HOLD_AIR_SWIM, element_.type_);
	}
}

// 終了時処理
void PlayerState_HoldAirBegin::onEnd() {}

// キー入力処理
void PlayerState_HoldAirBegin::onKeyInput(float deltaTime) {
	// 移動の入力がなくなった場合IDLE状態に遷移
	if ((!InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT) && element_.type_ == ActionType::Right) ||
		(!InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT) && element_.type_ == ActionType::Left)) {
		change(PlayerState_Enum_Union::IDLE);
	}
}

// パッド入力処理
void PlayerState_HoldAirBegin::onPadInput(float deltaTime) {
	// 移動の入力がなくなった場合IDLE状態に遷移
	if ((!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Right) ||
		(!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Left)) {
		change(PlayerState_Enum_Union::IDLE);
	}
}

// 移動処理
void PlayerState_HoldAirBegin::onMove(float deltaTime) {
	Vector2 gravity = Vector2::Up * GRAVITY * deltaTime * static_cast<float>(GetRefreshRate());

	butty_->position() += gravity / 2 * retty_->velocity();
	retty_->position() += gravity / 2 * butty_->velocity();
}

