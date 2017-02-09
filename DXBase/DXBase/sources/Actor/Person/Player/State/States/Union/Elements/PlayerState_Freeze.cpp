#include "PlayerState_Freeze.h"

#include "../../../../../../../Define.h"
#include "../../../../../../../Scene/Base/SceneDataKeeper.h"

PlayerState_Freeze::PlayerState_Freeze(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty) : PlayerState_Union(butty, retty) {}

void PlayerState_Freeze::unique_init(){
	butty_->animation().change(PlayerAnimID::IDLE);
	retty_->animation().change(PlayerAnimID::IDLE);

	timer_ = 0;

	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_SYOUTOTU), DX_PLAYTYPE_BACK);

	cntr_->getWorld()->GetKeeper()->comboReset(0);
}

void PlayerState_Freeze::update(float deltaTime){
	timer_ += deltaTime;

	if (timer_ >= PLAYER_FREEZE_TIME) change(PlayerState_Enum_Union::IDLE);
}

void PlayerState_Freeze::end(){}

void PlayerState_Freeze::key_input(float deltaTime){ 
	if (holdable_keyR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	if (holdable_keyL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
}

void PlayerState_Freeze::pad_input(float deltaTime){
	if (holdable_padR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	if (holdable_padL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
}

