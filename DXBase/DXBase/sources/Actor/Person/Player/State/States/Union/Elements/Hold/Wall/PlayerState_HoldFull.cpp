#include "PlayerState_HoldFull.h"

#include "../../../../../../Effect/PlayerEffectObj.h"

#include "../../../../../../../../../Define.h"
#include "../../../../../../../../../Input/InputMgr.h"
#include "../../../../../../../../../Scene/Base/SceneDataKeeper.h"

// コンストラクタ
PlayerState_HoldFull::PlayerState_HoldFull(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_HoldBase(butty, retty) {}

// 状態固有の初期化
void PlayerState_HoldFull::onInit(){
	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_NOBI_FULL), DX_PLAYTYPE_BACK);
	cntr_->world_->addActor(ActorGroup::Effect, std::make_shared<PlayerEffectObj>(cntr_->world_, cntr_->getPosition(), PlayerEffectID::SHOUGEKI, 3.0f, 5.0f));
}

// 更新処理	
void PlayerState_HoldFull::onUpdate(float deltaTime){
	cntr_->getWorld()->GetKeeper()->addChargeTime(deltaTime);

	if (retty_->distance() < PLAYER_MAX_STRETCH_LENGTH * 0.5f) {
		change(PlayerState_Enum_Union::HOLD_SWIM, element_.type_);
	}
}

// 終了時処理
void PlayerState_HoldFull::onEnd(){}

// キー入力処理
void PlayerState_HoldFull::onKeyInput(float deltaTime){
	if (!InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT) && element_.type_ == ActionType::Right) {
		change(PlayerState_Enum_Union::ATTACK_R);
	}
	if (!InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT) && element_.type_ == ActionType::Left) {
		change(PlayerState_Enum_Union::ATTACK_L);
	}

	if (InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT) && element_.type_ == ActionType::Left) {
		if (butty_->able_to_hold()) change(PlayerState_Enum_Union::HOLD_BOTH, ActionType::Left);
	}
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT) && element_.type_ == ActionType::Right) {
		if (retty_->able_to_hold()) change(PlayerState_Enum_Union::HOLD_BOTH, ActionType::Right);
	}
}

// パッド入力処理
void PlayerState_HoldFull::onPadInput(float deltaTime){
	if (!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Right) {
		change(PlayerState_Enum_Union::ATTACK_R);
	}
	if (!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Left) {
		change(PlayerState_Enum_Union::ATTACK_L);
	}

	if (InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Left) {
		if (butty_->able_to_hold()) {
			change(PlayerState_Enum_Union::HOLD_BOTH, ActionType::Left);
		}
	}
	if (InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Right) {
		if (retty_->able_to_hold()) {
			change(PlayerState_Enum_Union::HOLD_BOTH, ActionType::Right);
		}
	}
}

// 移動処理
void PlayerState_HoldFull::onMove(float deltaTime){
	Vector2 gravity = Vector2::Up * GRAVITY * deltaTime * static_cast<float>(GetRefreshRate());

	if (element_.type_ == ActionType::Left) {
		if (InputMgr::GetInstance().AnalogPadVectorR().Length() > 0) {
			gravity = Vector2::Zero;
		}
		butty_->position() += gravity * butty_->velocity();
	}
	if (element_.type_ == ActionType::Right) {
		if (InputMgr::GetInstance().AnalogPadVectorL().Length() > 0) {
			gravity = Vector2::Zero;
		}
		retty_->position() += gravity * retty_->velocity();
	}
}

