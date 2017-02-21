#include "PlayerState_HoldBegin.h"

#include "../../../../../../../../../Define.h"
#include "../../../../../../../../../Input/InputMgr.h"
#include "../../../../../../../../../Scene/Base/SceneDataKeeper.h"

// コンストラクタ
PlayerState_HoldBegin::PlayerState_HoldBegin(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_HoldBase(butty, retty) {}

// 状態固有の初期化
void PlayerState_HoldBegin::onInit(){
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

	cntr_->getWorld()->GetKeeper()->addHoldCount(1);
}

// 更新処理	
void PlayerState_HoldBegin::onUpdate(float deltaTime){
	// プレイヤーが一定距離離れたらHOLD_SWIM状態に遷移
	if (retty_->distance() >= PLAYER_SWIM_LENGTH) {
		change(PlayerState_Enum_Union::HOLD_SWIM, element_.type_);
	}
}

// 終了時処理
void PlayerState_HoldBegin::onEnd(){}

// キー入力処理
void PlayerState_HoldBegin::onKeyInput(float deltaTime){
	// 移動の入力がなくなった場合IDLE状態に遷移
	if ((!InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT) && element_.type_ == ActionType::Right) ||
		(!InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT) && element_.type_ == ActionType::Left)) {
		change(PlayerState_Enum_Union::IDLE);
	}

	if (InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT) && element_.type_ == ActionType::Left) {
		if (butty_->able_to_hold()) change(PlayerState_Enum_Union::HOLD_BOTH, ActionType::Left);
	}
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT) && element_.type_ == ActionType::Right) {
		if (retty_->able_to_hold()) change(PlayerState_Enum_Union::HOLD_BOTH, ActionType::Right);
	}
}

// パッド入力処理
void PlayerState_HoldBegin::onPadInput(float deltaTime){
	// 移動の入力がなくなった場合IDLE状態に遷移
	if ((!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Right) ||
		(!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Left)) {
		change(PlayerState_Enum_Union::IDLE);
	}

	if (InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Left) {
		if (butty_->able_to_hold()) {
			change(PlayerState_Enum_Union::HOLD_BOTH, ActionType::Left);
		}
	}
	if (InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Right) {
		if (retty_->able_to_hold()) {
			change(PlayerState_Enum_Union::HOLD_BOTH, ActionType::Right);
		}
	}
}

// 移動処理
void PlayerState_HoldBegin::onMove(float deltaTime){
	Vector2 gravity = Vector2::Up * GRAVITY * deltaTime * static_cast<float>(GetRefreshRate());

	if (element_.type_ == ActionType::Left) {
		if (InputMgr::GetInstance().AnalogPadVectorR().Length() > 0) {
			gravity = Vector2::Zero;
		}
		butty_->position() += gravity * butty_->velocity();
	}
	if (element_.type_ == ActionType::Right) {
		if (InputMgr::GetInstance().AnalogPadVectorL().Length() > 0) {
			gravity = Vector2::Zero;
		}
		retty_->position() += gravity * retty_->velocity();
	}
}
