#include "PlayerState_HoldBase_Begin.h"

#include "../../../../../../../../../Input/InputMgr.h"
#include "../../../../../../../../../Define.h"

PlayerState_HoldBase_Begin::PlayerState_HoldBase_Begin(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_HoldBase(butty, retty) {}

void PlayerState_HoldBase_Begin::onInit(){
	// アニメーションの変更
	moveBody_->animation().change(PlayerAnimID::SWIM);
	holdBody_->animation().change(PlayerAnimID::HOLD);

	//// くっつき時効果音再生
	//PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_SYOUTOTU), DX_PLAYTYPE_BACK);
}

void PlayerState_HoldBase_Begin::onEnd(){}

void PlayerState_HoldBase_Begin::onKeyInput(float deltaTime){
	// 移動の入力がなくなった場合IDLE状態に遷移
	if ((!InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT) && element_.type_ == ActionType::Left) ||
		(!InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT) && element_.type_ == ActionType::Right)) {
		change(PlayerState_Enum_Union::IDLE);
	}
}

void PlayerState_HoldBase_Begin::onPadInput(float deltaTime){
	// 移動の入力がなくなった場合IDLE状態に遷移
	if ((!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Left) ||
		(!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Right)) {
		change(PlayerState_Enum_Union::IDLE);
	}
}
