#include "PlayerState_AttackR.h"

#include "../../../../../../../../Define.h"
#include "../../../../../../../../Input/InputMgr.h"

PlayerState_AttackR::PlayerState_AttackR(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_AttackBase(butty, retty) {}

void PlayerState_AttackR::onInit(){
	launch_dir_ = Vector2::Normalize(retty_->getPosition() - butty_->getPosition());
	chase_dir_ = Vector2::Normalize(retty_->getPosition() - butty_->getPosition());
}

void PlayerState_AttackR::onUpdate(float deltaTime) {
	butty_->position() += (launch_dir_ * launch_dir_easeing_ * launch_power_ + Vector2::Up * GRAVITY * gra_easeing_) * butty_->velocity() * deltaTime * static_cast<float>(GetRefreshRate());
	retty_->position() += (chase_dir_ * chase_dir_easeing_ * chase_power_ + Vector2::Up * GRAVITY * gra_easeing_) * retty_->velocity() * deltaTime * static_cast<float>(GetRefreshRate());
	
	attackColl_->position() = butty_->getPosition();
}

void PlayerState_AttackR::onCollide(const Actor & other){}

void PlayerState_AttackR::onEnd(){}

void PlayerState_AttackR::onKeyInput(float deltaTime){
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT)) change(PlayerState_Enum_Union::HOLD_AIR, ActionType::Right);

}

void PlayerState_AttackR::onPadInput(float deltaTime){
	if (InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1)) change(PlayerState_Enum_Union::HOLD_AIR, ActionType::Right);
}
