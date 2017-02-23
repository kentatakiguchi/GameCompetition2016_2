#include "PlayerState_HoldBegin.h"

#include "../../../../../../../../../Define.h"
#include "../../../../../../../../../Input/InputMgr.h"
#include "../../../../../../../../../Scene/Base/SceneDataKeeper.h"

// �R���X�g���N�^
PlayerState_HoldBegin::PlayerState_HoldBegin(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_HoldBase(butty, retty) {}

// ��ԌŗL�̏�����
void PlayerState_HoldBegin::onInit(){}

// �X�V����	
void PlayerState_HoldBegin::onUpdate(float deltaTime){
	// �v���C���[����苗�����ꂽ��HOLD_SWIM��ԂɑJ��
	if (retty_->distance() >= PLAYER_SWIM_LENGTH) {
		change(PlayerState_Enum_Union::HOLD_SWIM, element_.type_);
	}
}

// �I��������
void PlayerState_HoldBegin::onEnd(){}

// �L�[���͏���
void PlayerState_HoldBegin::onKeyInput(float deltaTime){
	// �ړ��̓��͂��Ȃ��Ȃ����ꍇIDLE��ԂɑJ��
	if ((!InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT) && element_.type_ == ActionType::Right) ||
		(!InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT) && element_.type_ == ActionType::Left)) {
		change(PlayerState_Enum_Union::IDLE);
	}

	if (InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT) && element_.type_ == ActionType::Left) {
		if (butty_->getColliderOpponent() == HitOpponent::ITEM) {
			change(PlayerState_Enum_Union::HOLD_ITEM, element_.type_);
		}
		else if (butty_->able_to_hold()) change(PlayerState_Enum_Union::HOLD_BOTH, ActionType::Right);

	}
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT) && element_.type_ == ActionType::Right) {
		if (retty_->getColliderOpponent() == HitOpponent::ITEM) {
			change(PlayerState_Enum_Union::HOLD_ITEM, element_.type_);
		}
		else if (retty_->able_to_hold()) change(PlayerState_Enum_Union::HOLD_BOTH, ActionType::Left);
	}
}

// �p�b�h���͏���
void PlayerState_HoldBegin::onPadInput(float deltaTime){
	// �ړ��̓��͂��Ȃ��Ȃ����ꍇIDLE��ԂɑJ��
	if ((!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Right) ||
		(!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Left)) {
		change(PlayerState_Enum_Union::IDLE);
	}

	if (InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Left) {
		if (butty_->getColliderOpponent() == HitOpponent::ITEM) {
			change(PlayerState_Enum_Union::HOLD_ITEM, element_.type_);
		}
		else if (butty_->able_to_hold()) change(PlayerState_Enum_Union::HOLD_BOTH, ActionType::Right);
	}
	if (InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Right) {
		if (retty_->getColliderOpponent() == HitOpponent::ITEM) {
			change(PlayerState_Enum_Union::HOLD_ITEM, element_.type_);
		}
		else if (retty_->able_to_hold()) change(PlayerState_Enum_Union::HOLD_BOTH, ActionType::Left);
	}
}

// �ړ�����
void PlayerState_HoldBegin::onMove(float deltaTime){
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
