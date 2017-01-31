#include "PlayerState_HoldAirFull.h"

#include "../../../../../../Effect/PlayerEffectObj.h"

// コンストラクタ
PlayerState_HoldAirFull::PlayerState_HoldAirFull(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_HoldBase(butty, retty) {}

// 状態固有の初期化
void PlayerState_HoldAirFull::onInit() {
	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_NOBI_FULL), DX_PLAYTYPE_BACK);
	cntr_->world_->addActor(ActorGroup::Effect, std::make_shared<PlayerEffectObj>(cntr_->world_, cntr_->getPosition(), PlayerEffectID::SHOUGEKI, 3.0f, 5.0f));
}

// 更新処理	
void PlayerState_HoldAirFull::onUpdate(float deltaTime) {
	if (retty_->distance() < PLAYER_MAX_STRETCH_LENGTH * 0.6f) {
		change(PlayerState_Enum_Union::HOLD_AIR_SWIM, element_.type_);
	}
}

// 終了時処理
void PlayerState_HoldAirFull::onEnd() {}

// キー入力処理
void PlayerState_HoldAirFull::onKeyInput(float deltaTime) {
	if (!InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT) && element_.type_ == ActionType::Right) {
		change(PlayerState_Enum_Union::ATTACK, ActionType::Right);
	}
	if (!InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT) && element_.type_ == ActionType::Left) {
		change(PlayerState_Enum_Union::ATTACK, ActionType::Left);
	}
}

// パッド入力処理
void PlayerState_HoldAirFull::onPadInput(float deltaTime) {
	if (!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Right) {
		change(PlayerState_Enum_Union::ATTACK, ActionType::Right);
	}
	if (!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Left) {
		change(PlayerState_Enum_Union::ATTACK, ActionType::Left);
	}
}

// 移動処理
void PlayerState_HoldAirFull::onMove(float deltaTime) {
	Vector2 gravity = Vector2::Up * GRAVITY * deltaTime * static_cast<float>(GetRefreshRate());

	butty_->position() += gravity / 2 * retty_->velocity();
	retty_->position() += gravity / 2 * butty_->velocity();
}

