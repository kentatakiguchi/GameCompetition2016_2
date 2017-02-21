#include "PlayerState_AttackL.h"

#include "../../../../../../../../Define.h"
#include "../../../../../../../../Input/InputMgr.h"

PlayerState_AttackL::PlayerState_AttackL(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_AttackBase(butty, retty) {}

void PlayerState_AttackL::onInit(){
	launch_dir_ = Vector2::Normalize(butty_->getPosition() - retty_->getPosition());
	chase_dir_ = Vector2::Normalize(butty_->getPosition() - retty_->getPosition());
}

void PlayerState_AttackL::onUpdate(float deltaTime){
	retty_->position() += (launch_dir_ * launch_dir_easeing_ * launch_power_ + Vector2::Up * GRAVITY * gra_easeing_) * butty_->velocity() * deltaTime * static_cast<float>(GetRefreshRate());
	butty_->position() += (chase_dir_ * chase_dir_easeing_ * chase_power_ + Vector2::Up * GRAVITY * gra_easeing_) * retty_->velocity() * deltaTime * static_cast<float>(GetRefreshRate());

	attackColl_->position() = retty_->getPosition();
}

void PlayerState_AttackL::onCollide(const Actor & other){}

void PlayerState_AttackL::onEnd(){}

void PlayerState_AttackL::onKeyInput(float deltaTime){
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT)) change(PlayerState_Enum_Union::HOLD_AIR, ActionType::Left);
}

void PlayerState_AttackL::onPadInput(float deltaTime){
	if (InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1)) change(PlayerState_Enum_Union::HOLD_AIR, ActionType::Left);
}
