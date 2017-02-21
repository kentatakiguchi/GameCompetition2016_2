#include "PlayerState_HoldBoth.h"

#include "../../../../../../../../Input/InputMgr.h"
#include "../../../../../PlayerBodyCollider.h"
#include <memory>

PlayerState_HoldBoth::PlayerState_HoldBoth(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty) : PlayerState_Union(butty, retty) {}

void PlayerState_HoldBoth::unique_init() {
	butty_->animation().change(PlayerAnimID::HOLD);
	retty_->animation().change(PlayerAnimID::HOLD);

	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_SYOUTOTU), DX_PLAYTYPE_BACK);

	Vector2 holdPos = Vector2::Zero;
	if (element_.type_ == ActionType::Right) {
		holdPos = butty_->getPosition();
	}
	if (element_.type_ == ActionType::Left) {
		holdPos = retty_->getPosition();
	}
	cntr_->getWorld()->addActor(ActorGroup::Player_Collider, std::make_shared<PlayerBodyCollider>(cntr_->getWorld(), std::string("PlayerHold"), holdPos));
}

void PlayerState_HoldBoth::update(float deltaTime) {
	auto holdColl = cntr_->world_->findActor("PlayerHoldCollider");
	if (holdColl->getOpponent() == HitOpponent::ITEM) {
		change(PlayerState_Enum_Union::HOLD_ITEM, element_.type_);
	}
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

