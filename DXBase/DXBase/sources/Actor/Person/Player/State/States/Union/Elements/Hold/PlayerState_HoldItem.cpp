#include "PlayerState_HoldItem.h"

#include "../../../../../../../../Define.h"
#include "../../../../../../../../Input/InputMgr.h"
#include "../../../../../../../../Scene/Base/SceneDataKeeper.h"
#include "../../../../../PlayerBodyCollider.h"

PlayerState_HoldItem::PlayerState_HoldItem(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty):PlayerState_HoldBase(butty, retty){}

void PlayerState_HoldItem::onInit(){
	if (element_.type_ == ActionType::Right) {
		holdBody_ = retty_;
		moveBody_ = butty_;
	}
	if (element_.type_ == ActionType::Left) {
		holdBody_ = butty_;
		moveBody_ = retty_;
	}
	cntr_->getWorld()->addActor(ActorGroup::Player_Collider, std::make_shared<PlayerBodyCollider>(cntr_->getWorld(), std::string("PlayerHold")));
}

void PlayerState_HoldItem::onUpdate(float deltaTime){

	auto holdColl = cntr_->world_->findActor("PlayerHoldCollider");
	if (holdColl == nullptr)return;
	holdColl->position() = moveBody_->getPosition();
}

void PlayerState_HoldItem::onEnd(){
	auto holdColl = cntr_->world_->findActor("PlayerHoldCollider");
	if (holdColl != nullptr)holdColl->dead();
}

void PlayerState_HoldItem::onKeyInput(float deltaTime){
	// ˆÚ“®‚Ì“ü—Í‚ª‚È‚­‚È‚Á‚½ê‡IDLEó‘Ô‚É‘JˆÚ
	if (!InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT) && element_.type_ == ActionType::Right) {
		change(PlayerState_Enum_Union::HOLD_BEGIN, ActionType::Right);
	}
	if (!InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT) && element_.type_ == ActionType::Left) {
		change(PlayerState_Enum_Union::HOLD_BEGIN, ActionType::Left);
	}
}

void PlayerState_HoldItem::onPadInput(float deltaTime){
	// ˆÚ“®‚Ì“ü—Í‚ª‚È‚­‚È‚Á‚½ê‡IDLEó‘Ô‚É‘JˆÚ
	if (!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Right){
		change(PlayerState_Enum_Union::HOLD_BEGIN, ActionType::Right);
	}
	if (!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Left) {
		change(PlayerState_Enum_Union::HOLD_BEGIN, ActionType::Left);
	}
}

void PlayerState_HoldItem::onMove(float deltaTime){
	Vector2 gravity = Vector2::Up * GRAVITY * deltaTime * static_cast<float>(GetRefreshRate());

	if (InputMgr::GetInstance().PadVector(element_.type_).Length() > 0) {
		gravity = Vector2::Zero;
	}
	moveBody_->position() += gravity * moveBody_->velocity();
}
