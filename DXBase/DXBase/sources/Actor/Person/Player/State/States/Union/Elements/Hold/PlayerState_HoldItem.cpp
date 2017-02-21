#include "PlayerState_HoldItem.h"

#include "../../../../../../../../Define.h"
#include "../../../../../../../../Input/InputMgr.h"
#include "../../../../../../../../Scene/Base/SceneDataKeeper.h"

PlayerState_HoldItem::PlayerState_HoldItem(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty):PlayerState_HoldBase(butty, retty){}

void PlayerState_HoldItem::onInit(){}

void PlayerState_HoldItem::onUpdate(float deltaTime){
	auto holdColl = cntr_->world_->findActor("PlayerHoldCollider");
	if (holdColl == nullptr)return;
	if (element_.type_ == ActionType::Right) {
		holdColl->position() = retty_->getPosition();
	}
	if (element_.type_ == ActionType::Left) {
		holdColl->position() = butty_->getPosition();
	}
}

void PlayerState_HoldItem::onEnd(){
	auto holdColl = cntr_->world_->findActor("PlayerHoldCollider");
	holdColl->dead();
}

void PlayerState_HoldItem::onKeyInput(float deltaTime){
	// 移動の入力がなくなった場合IDLE状態に遷移
	if (!InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT) && element_.type_ == ActionType::Left) {
		change(PlayerState_Enum_Union::HOLD, ActionType::Left);
	}
	if (!InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT) && element_.type_ == ActionType::Right) {
		change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	}
}

void PlayerState_HoldItem::onPadInput(float deltaTime){
	// 移動の入力がなくなった場合IDLE状態に遷移
	if (!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Left){
		change(PlayerState_Enum_Union::HOLD, ActionType::Left);
	}
	if (!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Right) {
		change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	}
}

void PlayerState_HoldItem::onMove(float deltaTime){
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
