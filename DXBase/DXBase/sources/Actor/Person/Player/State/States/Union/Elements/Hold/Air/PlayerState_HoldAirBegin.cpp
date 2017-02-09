#include "PlayerState_HoldAirBegin.h"

#include "../../../../../../../../../Input/InputMgr.h"

#include "../../../../../../../../../Define.h"

// �R���X�g���N�^
PlayerState_HoldAirBegin::PlayerState_HoldAirBegin(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_HoldBase(butty, retty) {}

// ��ԌŗL�̏�����
void PlayerState_HoldAirBegin::onInit() {
	// �A�j���[�V�����̕ύX
	if (element_.type_ == ActionType::Right) {
		butty_->animation().change(PlayerAnimID::HOLD);
		retty_->animation().change(PlayerAnimID::SWIM);
	}
	if (element_.type_ == ActionType::Left) {
		retty_->animation().change(PlayerAnimID::HOLD);
		butty_->animation().change(PlayerAnimID::SWIM);
	}

	// �����������ʉ��Đ�
	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_SYOUTOTU), DX_PLAYTYPE_BACK);

}

// �X�V����	
void PlayerState_HoldAirBegin::onUpdate(float deltaTime) {
	// �v���C���[����苗�����ꂽ��HOLD_SWIM��ԂɑJ��
	if (retty_->distance() >= PLAYER_SWIM_LENGTH) {
		change(PlayerState_Enum_Union::HOLD_AIR_SWIM, element_.type_);
	}
}

// �I��������
void PlayerState_HoldAirBegin::onEnd() {}

// �L�[���͏���
void PlayerState_HoldAirBegin::onKeyInput(float deltaTime) {
	// �ړ��̓��͂��Ȃ��Ȃ����ꍇIDLE��ԂɑJ��
	if ((!InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT) && element_.type_ == ActionType::Right) ||
		(!InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT) && element_.type_ == ActionType::Left)) {
		change(PlayerState_Enum_Union::IDLE);
	}
}

// �p�b�h���͏���
void PlayerState_HoldAirBegin::onPadInput(float deltaTime) {
	// �ړ��̓��͂��Ȃ��Ȃ����ꍇIDLE��ԂɑJ��
	if ((!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Right) ||
		(!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Left)) {
		change(PlayerState_Enum_Union::IDLE);
	}
}

// �ړ�����
void PlayerState_HoldAirBegin::onMove(float deltaTime) {
	Vector2 gravity = Vector2::Up * GRAVITY * deltaTime * static_cast<float>(GetRefreshRate());

	butty_->position() += gravity / 2 * retty_->velocity();
	retty_->position() += gravity / 2 * butty_->velocity();
}

