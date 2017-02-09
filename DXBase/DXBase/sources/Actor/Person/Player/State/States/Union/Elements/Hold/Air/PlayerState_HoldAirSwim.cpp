#include "PlayerState_HoldAirSwim.h"

#include "../../../../../../../../../Define.h"
#include "../../../../../../../../../Input/InputMgr.h"
#include "../../../../../../../../../Scene/Base/SceneDataKeeper.h"

// �R���X�g���N�^
PlayerState_HoldAirSwim::PlayerState_HoldAirSwim(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_HoldBase(butty, retty) {}

// ��ԌŗL�̏�����
void PlayerState_HoldAirSwim::onInit() {
	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_NOBI), DX_PLAYTYPE_LOOP);
}

// �X�V����	
void PlayerState_HoldAirSwim::onUpdate(float deltaTime) {
	cntr_->getWorld()->GetKeeper()->addChargeTime(deltaTime);

	if (retty_->distance() < PLAYER_SWIM_LENGTH) {
		change(PlayerState_Enum_Union::HOLD_AIR, element_.type_);
	}
	if (retty_->distance() >= PLAYER_MAX_STRETCH_LENGTH * 0.7f) {
		change(PlayerState_Enum_Union::HOLD_AIR_FULL, element_.type_);
	}
}

// �I��������
void PlayerState_HoldAirSwim::onEnd() {
	StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_NOBI));
}

// �L�[���͏���
void PlayerState_HoldAirSwim::onKeyInput(float deltaTime) {
	if ((!InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT) && element_.type_ == ActionType::Right) ||
		(!InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT) && element_.type_ == ActionType::Left)) {
		change(PlayerState_Enum_Union::IDLE);
	}
}

// �p�b�h���͏���
void PlayerState_HoldAirSwim::onPadInput(float deltaTime) {
	if ((!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Right) ||
		(!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Left)) {
		change(PlayerState_Enum_Union::IDLE);
	}
}

// �ړ�����
void PlayerState_HoldAirSwim::onMove(float deltaTime) {
	Vector2 gravity = Vector2::Up * GRAVITY * deltaTime * static_cast<float>(GetRefreshRate());

	butty_->position() += gravity / 2 * retty_->velocity();
	retty_->position() += gravity / 2 * butty_->velocity();
}
