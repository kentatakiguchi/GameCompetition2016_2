#include "PlayerState_HoldBase_Full.h"

#include "../../../../../../Effect/PlayerEffectObj.h"

#include "../../../../../../../../../Define.h"
#include "../../../../../../../../../Input/InputMgr.h"

PlayerState_HoldBase_Full::PlayerState_HoldBase_Full(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_HoldBase(butty, retty) {}

void PlayerState_HoldBase_Full::onInit(){
	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_NOBI_FULL), DX_PLAYTYPE_BACK);
	cntr_->world_->addActor(ActorGroup::Effect, std::make_shared<PlayerEffectObj>(cntr_->world_, cntr_->getPosition(), PlayerEffectID::SHOUGEKI, 3.0f, 5.0f));
}

void PlayerState_HoldBase_Full::onEnd(){}

void PlayerState_HoldBase_Full::onKeyInput(float deltaTime){
	if ((!InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT) && element_.type_ == ActionType::Left) ||
		(!InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT) && element_.type_ == ActionType::Right)) {
		change(PlayerState_Enum_Union::ATTACK, element_.type_);
	}
}

void PlayerState_HoldBase_Full::onPadInput(float deltaTime){
	if ((!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Left) ||
		(!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Right)) {
		change(PlayerState_Enum_Union::ATTACK, element_.type_);
	}
}

