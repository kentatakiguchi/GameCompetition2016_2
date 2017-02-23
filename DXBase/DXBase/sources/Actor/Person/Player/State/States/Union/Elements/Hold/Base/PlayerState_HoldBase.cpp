#include "PlayerState_HoldBase.h"

#include "../../../../../../../../../Define.h"
#include "../../../../../../../../../Input/InputMgr.h"
#include "../../../../../../../../../Scene/Base/SceneDataKeeper.h"

PlayerState_HoldBase::PlayerState_HoldBase(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_Union(butty, retty) {}

void PlayerState_HoldBase::unique_init(){
	if (element_.type_ == ActionType::Right) {
		moveBody_ = butty_;
		holdBody_ = retty_;
	}
	if (element_.type_ == ActionType::Left) {
		moveBody_ = retty_;
		holdBody_ = butty_;
	}

	onInit();
}

void PlayerState_HoldBase::update(float deltaTime){
	cntr_->getWorld()->GetKeeper()->addChargeTime(deltaTime);

	onUpdate(deltaTime);

	move(deltaTime);
}

void PlayerState_HoldBase::end(){
	onEnd();
}

void PlayerState_HoldBase::key_input(float deltaTime){
	moveBody_->position() += InputMgr::GetInstance().KeyVector(element_.type_) * 7.5f * moveBody_->velocity() * PLAYER_SPEED * moveBody_->dump() * deltaTime * static_cast<float>(GetRefreshRate());
	
	//if (element_.type_ == ActionType::Right) retty_->position() += InputMgr::GetInstance().KeyVector(KeyCode::D, KeyCode::A, KeyCode::W, KeyCode::S) * 7.5f * speed_r(deltaTime);
	//if (element_.type_ == ActionType::Left)  butty_->position() += InputMgr::GetInstance().KeyVector() * 7.5f * speed_b(deltaTime);

	if (InputMgr::GetInstance().KeyVector(element_.type_).x > 0) moveBody_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Right);
	if (InputMgr::GetInstance().KeyVector(element_.type_).x < 0) moveBody_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Left);

	//if (element_.type_ == ActionType::Right) {
	//	if (InputMgr::GetInstance().KeyVectorL().x > 0) retty_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Right);
	//	if (InputMgr::GetInstance().KeyVectorL().x < 0) retty_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Left);
	//}
	//if (element_.type_ == ActionType::Left) {
	//	if (InputMgr::GetInstance().KeyVectorR().x > 0) butty_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Right);
	//	if (InputMgr::GetInstance().KeyVectorR().x < 0) butty_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Left);
	//}

	onKeyInput(deltaTime);
}

void PlayerState_HoldBase::pad_input(float deltaTime){
	moveBody_->position() += InputMgr::GetInstance().PadVector(element_.type_) * 7.5f * moveBody_->velocity() * PLAYER_SPEED * moveBody_->dump() * deltaTime * static_cast<float>(GetRefreshRate());

	//if (element_.type_ == ActionType::Right) retty_->position() += InputMgr::GetInstance().AnalogPadVectorL() * 7.5f * speed_r(deltaTime);
	//if (element_.type_ == ActionType::Left)  butty_->position() += InputMgr::GetInstance().AnalogPadVectorR() * 7.5f * speed_b(deltaTime);;

	if (InputMgr::GetInstance().PadVector(element_.type_).x > 0) moveBody_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Right);
	if (InputMgr::GetInstance().PadVector(element_.type_).x < 0) moveBody_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Left);

	//if (element_.type_ == ActionType::Right) {
	//	if (InputMgr::GetInstance().AnalogPadVectorL().x > 0) retty_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Right);
	//	if (InputMgr::GetInstance().AnalogPadVectorL().x < 0) retty_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Left);
	//}
	//if (element_.type_ == ActionType::Left) {
	//	if (InputMgr::GetInstance().AnalogPadVectorR().x > 0) butty_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Right);
	//	if (InputMgr::GetInstance().AnalogPadVectorR().x < 0) butty_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Left);
	//}

	onPadInput(deltaTime);
}

void PlayerState_HoldBase::move(float deltaTime) {
	
	onMove(deltaTime);

	if (element_.type_ == ActionType::Right) {
		butty_->position() = clamp(butty_->position(), 0);
	}
	if (element_.type_ == ActionType::Left) {
		retty_->position() = clamp(retty_->position(), PLAYER_CNTR_DIV_NUM - 1);
	}

	retty_->reset_slope();
	butty_->reset_slope();
}

//void PlayerState_HoldBase::onInit(){}
//
//void PlayerState_HoldBase::onUpdate(float deltaTime){}
//
//void PlayerState_HoldBase::onEnd(){}
//
//void PlayerState_HoldBase::onKeyInput(float deltaTime){}
//
//void PlayerState_HoldBase::onPadInput(float deltaTime){}
//
//void PlayerState_HoldBase::onMove(float deltaTime){}

