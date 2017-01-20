#include "PlayerState_Single_LeanBack.h"

PlayerState_Single_LeanBack::PlayerState_Single_LeanBack(const Keys& keys) : PlayerState_Single(keys) {}

void PlayerState_Single_LeanBack::unique_init(){
	body_->animation().change(PlayerAnimID::DAMAGE);

	PlaySound("./resources/sounds/bunri.mp3" , DX_PLAYTYPE_BACK);

	body_->reset_opponent();

	dir_ = Vector2(body_->get_partner_vector().x, 1) * -1;
	power_ = PLAYER_LEANBACK_POWER;
	body_->launch(dir_ * power_);
}

void PlayerState_Single_LeanBack::update(float deltaTime) {
	dir_.y += 0.1f;

	body_->launch(dir_ * power_);

	if (body_->is_hit()) {
		change(StateElement((unsigned int)PlayerState_Enum_Single::IDLE));
	}
}

void PlayerState_Single_LeanBack::end(){
	body_->reset_dead_limit();

	body_->reset_enemy();

	body_->reset_slope();
}

