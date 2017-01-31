#include "PlayerState_HoldAirFull.h"

#include "../../../../../../Effect/PlayerEffectObj.h"

// �R���X�g���N�^
PlayerState_HoldAirFull::PlayerState_HoldAirFull(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_HoldBase(butty, retty) {}

// ��ԌŗL�̏�����
void PlayerState_HoldAirFull::onInit() {
	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_NOBI_FULL), DX_PLAYTYPE_BACK);
	cntr_->world_->addActor(ActorGroup::Effect, std::make_shared<PlayerEffectObj>(cntr_->world_, cntr_->getPosition(), PlayerEffectID::SHOUGEKI, 3.0f, 5.0f));
}

// �X�V����	
void PlayerState_HoldAirFull::onUpdate(float deltaTime) {
	if (retty_->distance() < PLAYER_MAX_STRETCH_LENGTH * 0.6f) {
		change(PlayerState_Enum_Union::HOLD_AIR_SWIM, element_.type_);
	}
}

// �I��������
void PlayerState_HoldAirFull::onEnd() {}

// �L�[���͏���
void PlayerState_HoldAirFull::onKeyInput(float deltaTime) {
	if (!InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT) && element_.type_ == ActionType::Right) {
		change(PlayerState_Enum_Union::ATTACK, ActionType::Right);
	}
	if (!InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT) && element_.type_ == ActionType::Left) {
		change(PlayerState_Enum_Union::ATTACK, ActionType::Left);
	}
}

// �p�b�h���͏���
void PlayerState_HoldAirFull::onPadInput(float deltaTime) {
	if (!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Right) {
		change(PlayerState_Enum_Union::ATTACK, ActionType::Right);
	}
	if (!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Left) {
		change(PlayerState_Enum_Union::ATTACK, ActionType::Left);
	}
}

// �ړ�����
void PlayerState_HoldAirFull::onMove(float deltaTime) {
	Vector2 gravity = Vector2::Up * GRAVITY * deltaTime * static_cast<float>(GetRefreshRate());

	butty_->position() += gravity / 2 * retty_->velocity();
	retty_->position() += gravity / 2 * butty_->velocity();
}

