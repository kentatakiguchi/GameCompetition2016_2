#include "PlayerState_Attack.h"

#include <algorithm>

PlayerState_Attack::PlayerState_Attack(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty) : PlayerState_Union(butty, retty) {}

void PlayerState_Attack::unique_init(){
	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_SHOT), DX_PLAYTYPE_BACK);

	butty_->reset_opponent();
	retty_->reset_opponent();

	if (element_.type_ == ActionType::Right) {
		launch_dir_ = Vector2::Normalize(retty_->getPosition() - butty_->getPosition());
		chase_dir_ = Vector2::Normalize(retty_->getPosition() - butty_->getPosition());
	}
	if (element_.type_ == ActionType::Left) {
		launch_dir_ = Vector2::Normalize(butty_->getPosition() - retty_->getPosition());
		chase_dir_ = Vector2::Normalize(butty_->getPosition() - retty_->getPosition());
	}
	launch_power_ = PLAYER_LAUNCH_POWER;
	chase_power_ = PLAYER_LAUNCH_POWER * 0.65f;
	launch_dir_easeing_ = 0;
	chase_dir_easeing_ = 0;
	gra_easeing_ = 0;

	// çUåÇîªíËÇÃê∂ê¨
	auto attackColl = std::make_shared<PlayerBodyCollider>(cntr_->getWorld(), std::string("PlayerAttack"));
	cntr_->getWorld()->addActor(ActorGroup::Player_Collider, attackColl);
	attackColl_ = attackColl;

	//cntr_->getWorld()->GetKeeper()->addJumpCount(1);
}

void PlayerState_Attack::update(float deltaTime) {
	timer_ += deltaTime;
	//timer_ = std::min<float>(timer_ + deltaTime, 1);

	launch_dir_easeing_ = -EasingOutExpo(timer_ * 0.7f) + 1;
	chase_dir_easeing_ = EasingSinCurve(std::max<float>(timer_ - 0.1f, 0) * 3.0f);
	gra_easeing_ = std::min<float>(EasingInExpo(timer_ * 0.8f), 1);

	if (element_.type_ == ActionType::Right) {
		butty_->position() += (launch_dir_ * launch_dir_easeing_ * launch_power_ + Vector2::Up * GRAVITY * gra_easeing_) * butty_->velocity() * deltaTime * static_cast<float>(GetRefreshRate());
		retty_->position() += (chase_dir_ * chase_dir_easeing_ * chase_power_ + Vector2::Up * GRAVITY * gra_easeing_) * retty_->velocity() * deltaTime * static_cast<float>(GetRefreshRate());
	}
	if (element_.type_ == ActionType::Left) {
		retty_->position() += (launch_dir_ * launch_dir_easeing_ * launch_power_ + Vector2::Up * GRAVITY * gra_easeing_) * butty_->velocity() * deltaTime * static_cast<float>(GetRefreshRate());
		butty_->position() += (chase_dir_ * chase_dir_easeing_ * chase_power_ + Vector2::Up * GRAVITY * gra_easeing_) * retty_->velocity() * deltaTime * static_cast<float>(GetRefreshRate());
	}

	if (butty_->able_to_hold() && retty_->able_to_hold()) {
		change(PlayerState_Enum_Union::FREEZE);
	}

	if (element_.type_ == ActionType::Right) attackColl_->position() = butty_->getPosition();
	if (element_.type_ == ActionType::Left)	 attackColl_->position() = retty_->getPosition();

	if (butty_->hit_enemy() == HitOpponent::BOSS || retty_->hit_enemy() == HitOpponent::BOSS) {
		if (launch_dir_.x > 0) {
			change(PlayerState_Enum_Union::LEAN_BACK, ActionType::Left);
		}
		else {
			change(PlayerState_Enum_Union::LEAN_BACK, ActionType::Right);
		}
	}

	if (cntr_->getWorld()->isEntered()) change(PlayerState_Enum_Union::EVENT);
}

void PlayerState_Attack::end(){
	// çUåÇîªíËÇÃçÌèú
	attackColl_->dead();
	attackColl_ = nullptr;

	butty_->reset_enemy();
	retty_->reset_enemy();
}

void PlayerState_Attack::key_input(float deltaTime){
	if (holdable_keyR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	if (holdable_keyL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);

	if (InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT) && element_.type_ == ActionType::Left) change(PlayerState_Enum_Union::HOLD_AIR, ActionType::Left);
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT) && element_.type_ == ActionType::Right) change(PlayerState_Enum_Union::HOLD_AIR, ActionType::Right);
}

void PlayerState_Attack::pad_input(float deltaTime){
	if (holdable_padR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	if (holdable_padL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);

	if (InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Left) change(PlayerState_Enum_Union::HOLD_AIR, ActionType::Left);
	if (InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Right) change(PlayerState_Enum_Union::HOLD_AIR, ActionType::Right);
}
