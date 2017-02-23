#include "PlayerState_HoldBase_Swim.h"

#include "../../../../../../../../../Define.h"
#include "../../../../../../../../../Input/InputMgr.h"

PlayerState_HoldBase_Swim::PlayerState_HoldBase_Swim(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_HoldBase(butty, retty) {}

void PlayerState_HoldBase_Swim::onInit(){
	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_NOBI), DX_PLAYTYPE_LOOP);
}

void PlayerState_HoldBase_Swim::onEnd(){
	StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_NOBI));
}

void PlayerState_HoldBase_Swim::onKeyInput(float deltaTime){
	// ˆÚ“®‚Ì“ü—Í‚ª‚È‚­‚È‚Á‚½ê‡IDLEó‘Ô‚É‘JˆÚ
	if ((!InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT) && element_.type_ == ActionType::Left) ||
		(!InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT) && element_.type_ == ActionType::Right)) {
		change(PlayerState_Enum_Union::IDLE);
	}
}

void PlayerState_HoldBase_Swim::onPadInput(float deltaTime){
	// ˆÚ“®‚Ì“ü—Í‚ª‚È‚­‚È‚Á‚½ê‡IDLEó‘Ô‚É‘JˆÚ
	if ((!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Left) ||
		(!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Right)) {
		change(PlayerState_Enum_Union::IDLE);
	}
}
