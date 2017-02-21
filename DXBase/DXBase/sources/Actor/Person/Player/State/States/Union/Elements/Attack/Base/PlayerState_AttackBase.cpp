#include "PlayerState_AttackBase.h"

#include "../../../../../../../../../Define.h"
#include "../../../../../../../../../Input/InputMgr.h"
#include "../../../../../../../../../Scene/Base/SceneDataKeeper.h"

#include <algorithm>

PlayerState_AttackBase::PlayerState_AttackBase(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty) :
	PlayerState_Union(butty, retty),
	dir_(Vector2::Zero), launch_dir_(Vector2::Zero),
	launch_power_(0), launch_dir_easeing_(0),
	chase_dir_(Vector2::Zero), chase_power_(0), chase_dir_easeing_(0),
	gravity_(Vector2::Zero), gra_easeing_(0) {}

void PlayerState_AttackBase::unique_init() {
	onInit();

	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_SHOT), DX_PLAYTYPE_BACK);

	butty_->reset_opponent();
	retty_->reset_opponent();

	launch_power_ = PLAYER_LAUNCH_POWER;
	chase_power_ = PLAYER_LAUNCH_POWER * 0.65f;
	launch_dir_easeing_ = 0;
	chase_dir_easeing_ = 0;
	gra_easeing_ = 0;

	// çUåÇîªíËÇÃê∂ê¨
	auto attackColl = std::make_shared<PlayerBodyCollider>(cntr_->getWorld(), std::string("PlayerAttack"));
	cntr_->getWorld()->addActor(ActorGroup::Player_Collider, attackColl);
	attackColl_ = attackColl;

	cntr_->getWorld()->GetKeeper()->addComboCount(1, 1);
}

void PlayerState_AttackBase::update(float deltaTime) {
	timer_ += deltaTime;
	//timer_ = std::min<float>(timer_ + deltaTime, 1);

	launch_dir_easeing_ = -EasingOutExpo(timer_ * 0.7f) + 1;
	chase_dir_easeing_ = EasingSinCurve(std::max<float>(timer_ - 0.1f, 0) * 3.0f);
	gra_easeing_ = std::min<float>(EasingInExpo(timer_ * 0.8f), 1);
	
	if (butty_->able_to_hold() && retty_->able_to_hold()) {
		change(PlayerState_Enum_Union::IDLE);
	}


	if (butty_->hit_enemy() == HitOpponent::BOSS || retty_->hit_enemy() == HitOpponent::BOSS) {
		if (launch_dir_.x > 0) {
			change(PlayerState_Enum_Union::LEAN_BACK, ActionType::Left);
		}
		else {
			change(PlayerState_Enum_Union::LEAN_BACK, ActionType::Right);
		}
	}

	if (cntr_->getWorld()->isEntered()) change(PlayerState_Enum_Union::EVENT);

	onUpdate(deltaTime);
}

void PlayerState_AttackBase::end() {
	// çUåÇîªíËÇÃçÌèú
	attackColl_->dead();
	attackColl_ = nullptr;

	butty_->reset_enemy();
	retty_->reset_enemy();

	onEnd();
}

void PlayerState_AttackBase::key_input(float deltaTime) {
	if (holdable_keyR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	if (holdable_keyL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);

	onKeyInput(deltaTime);
}

void PlayerState_AttackBase::pad_input(float deltaTime) {
	if (holdable_padR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	if (holdable_padL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);

	onPadInput(deltaTime);
}
