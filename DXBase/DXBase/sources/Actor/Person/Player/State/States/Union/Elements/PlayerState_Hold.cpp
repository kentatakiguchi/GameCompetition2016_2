#include "PlayerState_Hold.h"

#include "../../../../Effect/PlayerEffectObj.h"

// コンストラクタ
PlayerState_Hold::PlayerState_Hold(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty) : PlayerState_Union(butty, retty) {}

// 状態固有の初期化
void PlayerState_Hold::unique_init(){
	if (element_.type_ == ActionType::Right) {
		butty_->animation().change(PlayerAnimID::HOLD);
		retty_->animation().change(PlayerAnimID::SWIM);
	}
	if (element_.type_ == ActionType::Left) {
		retty_->animation().change(PlayerAnimID::HOLD);
		butty_->animation().change(PlayerAnimID::SWIM);
	}

	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_SYOUTOTU), DX_PLAYTYPE_BACK);
}

// 更新処理
void PlayerState_Hold::update(float deltaTime) {
	if (retty_->distance() < PLAYER_MAX_STRETCH_LENGTH * 0.4f) {
		StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_NOBI));
		flag1_ = false;
		flag2_ = false;
	}
	else if (retty_->distance() < PLAYER_MAX_STRETCH_LENGTH * 0.7f) {
		flag2_ = false;
		if (!flag1_) {
			PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_NOBI), DX_PLAYTYPE_LOOP);
			flag1_ = true;
		}
	}
	else {
		flag1_ = false;
		if (!flag2_) {
			StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_NOBI));
			PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_NOBI_FULL), DX_PLAYTYPE_BACK);
			flag2_ = true;
			cntr_->world_->addActor(ActorGroup::Effect, std::make_shared<PlayerEffectObj>(cntr_->world_, cntr_->getPosition(), PlayerEffectID::SHOUGEKI, 3.0f, 5.0f));
		}
	}
	if (element_.type_ == ActionType::Right) {
		if (InputMgr::GetInstance().AnalogPadVectorL().x > 0) retty_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Right);
		if (InputMgr::GetInstance().AnalogPadVectorL().x < 0) retty_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Left);
	}
	if (element_.type_ == ActionType::Left) {
		if (InputMgr::GetInstance().AnalogPadVectorR().x > 0) butty_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Right);
		if (InputMgr::GetInstance().AnalogPadVectorR().x < 0) butty_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Left);
	}

	move(deltaTime);
}

// 終了時処理
void PlayerState_Hold::end(){
	StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_NOBI));
}

// キー入力処理
void PlayerState_Hold::key_input(float deltaTime){
	if (element_.type_ == ActionType::Right) retty_->position() += InputMgr::GetInstance().KeyVector(KeyCode::D, KeyCode::A, KeyCode::W, KeyCode::S) * 7.5f * PLAYER_SPEED * retty_->velocity() * deltaTime * static_cast<float>(GetRefreshRate());
	if (element_.type_ == ActionType::Left)  butty_->position() += InputMgr::GetInstance().KeyVector() * 7.5f * PLAYER_SPEED * butty_->velocity() * deltaTime * static_cast<float>(GetRefreshRate());

	if (!InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT) && element_.type_ == ActionType::Right) {
		if (retty_->distance() >= PLAYER_MAX_STRETCH_LENGTH * 0.8f)change(PlayerState_Enum_Union::ATTACK, ActionType::Right);
		else change(PlayerState_Enum_Union::IDLE);
	}
	if (!InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT) && element_.type_ == ActionType::Left) {
		if (butty_->distance() >= PLAYER_MAX_STRETCH_LENGTH * 0.8f)change(PlayerState_Enum_Union::ATTACK, ActionType::Left);
		else change(PlayerState_Enum_Union::IDLE);
	}

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT) && element_.type_ == ActionType::Left) {
		if (butty_->able_to_hold()) change(PlayerState_Enum_Union::HOLD_BOTH);
	}
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT) && element_.type_ == ActionType::Right) {
		if (retty_->able_to_hold()) change(PlayerState_Enum_Union::HOLD_BOTH);
	}
}

// パッド入力処理
void PlayerState_Hold::pad_input(float deltaTime){
	if (element_.type_ == ActionType::Right) retty_->position() += InputMgr::GetInstance().AnalogPadVectorL() * 7.5f * PLAYER_SPEED * retty_->velocity() * deltaTime * static_cast<float>(GetRefreshRate());
	if (element_.type_ == ActionType::Left)  butty_->position() += InputMgr::GetInstance().AnalogPadVectorR() * 7.5f * PLAYER_SPEED * butty_->velocity() * deltaTime * static_cast<float>(GetRefreshRate());

	if (!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Right) {
		if (retty_->distance() >= PLAYER_MAX_STRETCH_LENGTH * 0.8f)change(PlayerState_Enum_Union::ATTACK, ActionType::Right);
		else change(PlayerState_Enum_Union::IDLE);
	}
	if (!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Left) {
		if (butty_->distance() >= PLAYER_MAX_STRETCH_LENGTH * 0.8f)change(PlayerState_Enum_Union::ATTACK, ActionType::Left);
		else change(PlayerState_Enum_Union::IDLE);
	}

	if (InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Left) {
		if (butty_->able_to_hold()) change(PlayerState_Enum_Union::HOLD_BOTH);
	}
	if (InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Right) {
		if (retty_->able_to_hold()) change(PlayerState_Enum_Union::HOLD_BOTH);
	}
}

// 移動処理
void PlayerState_Hold::move(float deltaTime){
	Vector2 gravity = Vector2::Up * GRAVITY* deltaTime * static_cast<float>(GetRefreshRate());

	if (element_.type_ == ActionType::Left) {
		if (InputMgr::GetInstance().AnalogPadVectorR().Length() > 0) {
			gravity = Vector2::Zero;
		}
		butty_->position() += gravity * butty_->velocity();
		butty_->position() = clamp(butty_->position(), 0);
	}
	if (element_.type_ == ActionType::Right) {
		if (InputMgr::GetInstance().AnalogPadVectorL().Length() > 0) {
			gravity = Vector2::Zero;
		}
		retty_->position() += gravity * retty_->velocity();
		retty_->position() = clamp(retty_->position(), PLAYER_CNTR_DIV_NUM - 1);
	}

	retty_->reset_slope();
	butty_->reset_slope();
}


