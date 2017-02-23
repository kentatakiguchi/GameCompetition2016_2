#include "PlayerState_HoldBase_Wall.h"

#include "../../../../../../../../../Define.h"
#include "../../../../../../../../../Input/InputMgr.h"

PlayerState_HoldBase_Wall::PlayerState_HoldBase_Wall(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_HoldBase(butty, retty) {}

void PlayerState_HoldBase_Wall::onUpdate(float deltaTime){
	if (moveBody_->distance() < PLAYER_SWIM_LENGTH) change(PlayerState_Enum_Union::HOLD_BEGIN, element_.type_);
	else if (moveBody_->distance() < PLAYER_MAX_STRETCH_LENGTH * 0.7f) change(PlayerState_Enum_Union::HOLD_SWIM, element_.type_);
	else change(PlayerState_Enum_Union::HOLD_FULL, element_.type_);
}

void PlayerState_HoldBase_Wall::onKeyInput(float deltaTime){
	if ((InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT) && element_.type_ == ActionType::Right) ||
		(InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT) && element_.type_ == ActionType::Left)) {
		if (moveBody_->getColliderOpponent() == HitOpponent::ITEM) change(PlayerState_Enum_Union::HOLD_ITEM, element_.type_);
		else if (moveBody_->getColliderOpponent() == HitOpponent::FLOOR_HIT) change(PlayerState_Enum_Union::HOLD_BOTH, element_.type_);
	}
}

void PlayerState_HoldBase_Wall::onPadInput(float deltaTime){
	if ((InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Right) ||
		(InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Left)) {
		if (moveBody_->getColliderOpponent() == HitOpponent::ITEM) change(PlayerState_Enum_Union::HOLD_ITEM, element_.type_);
		else if (moveBody_->getColliderOpponent() == HitOpponent::FLOOR_HIT) change(PlayerState_Enum_Union::HOLD_BOTH, element_.type_);
	}
}

void PlayerState_HoldBase_Wall::onMove(float deltaTime){
	Vector2 gravity = Vector2::Up * GRAVITY * deltaTime * static_cast<float>(GetRefreshRate());

	if (InputMgr::GetInstance().PadVector(element_.type_).Length() > 0) {
		gravity = Vector2::Zero;
	}
	moveBody_->position() += gravity * moveBody_->velocity();
}
