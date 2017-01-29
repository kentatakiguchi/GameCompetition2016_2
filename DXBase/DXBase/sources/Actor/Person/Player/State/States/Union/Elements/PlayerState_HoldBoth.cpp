#include "PlayerState_HoldBoth.h"

PlayerState_HoldBoth::PlayerState_HoldBoth(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty) : PlayerState_Union(butty, retty) {}

void PlayerState_HoldBoth::unique_init() {
	butty_->animation().change(PlayerAnimID::HOLD);
	retty_->animation().change(PlayerAnimID::HOLD);

	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_SYOUTOTU), DX_PLAYTYPE_BACK);
}

void PlayerState_HoldBoth::update(float deltaTime) {
}

void PlayerState_HoldBoth::end() {}

void PlayerState_HoldBoth::key_input(float deltaTime){

	if (!InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT)) {
		change(PlayerState_Enum_Union::HOLD, ActionType::Left);
	}
	if (!InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT)) {
		change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	}
}

void PlayerState_HoldBoth::pad_input(float deltaTime){

	if (!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1)) {
		change(PlayerState_Enum_Union::HOLD, ActionType::Left);
	}
	if (!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1)) {
		change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	}
}

