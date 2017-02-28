#include "PlayerState_MoveEach.h"

#include "../../../../../../../../Define.h"
#include "../../../../../../../../Input/InputMgr.h"

// �R���X�g���N�^
PlayerState_MoveEach::PlayerState_MoveEach(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty) : PlayerState_Union(butty, retty) {}

// ��ԌŗL�̏�����
void PlayerState_MoveEach::unique_init(){

	if (element_.type_ == ActionType::Right) {
		manuBody_ = butty_;
		autoBody_ = retty_;
	}
	if (element_.type_ == ActionType::Left) {
		manuBody_ = retty_;
		autoBody_ = butty_;
	}

	// butty�̃A�j���[�V������MOVE�ɕύX
	butty_->animation().change(PlayerAnimID::MOVE, 2.0f);
	// retty�̃A�j���[�V������MOVE�ɕύX
	retty_->animation().change(PlayerAnimID::MOVE, 2.0f);
}

// �X�V����
void PlayerState_MoveEach::update(float deltaTime){
	// �A�j���[�V�������]
	flip_animation();

	// �ړ�����
	move(deltaTime);

	// �{�X�X�e�[�W��p�C�x���g����Event��ԂɕύX
	if (cntr_->getWorld()->isEntered()) change(PlayerState_Enum_Union::EVENT);
}

// �I��������
void PlayerState_MoveEach::end(){}

// �p�b�h���͏���
void PlayerState_MoveEach::input(float deltaTime){
	// butty�̓��͂ɂ�锽�]����
	if (InputMgr::GetInstance().PadVector(element_.type_).x > 0) manuBody_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().PadVector(element_.type_).x < 0) manuBody_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	// ���͂ɂ��ړ�����
	manuBody_->position() += InputMgr::GetInstance().PadVector(element_.type_).Horizontal() * manuBody_->velocity() * PLAYER_SPEED * manuBody_->dump() * time(deltaTime);

	// �W�����v����
	if (jump_pad()) change(PlayerState_Enum_Union::JUMP);
	// �ړ����͂��Ȃ��ꍇIDLE�ɕύX
	else if (!move_padR() && !move_padL()) change(PlayerState_Enum_Union::IDLE);
	// ���ړ��L�[�����͂��ꂽ�ꍇ��Ԃ�MOVE_BOTH�ɕύX
	else if (InputMgr::GetInstance().AnalogPadVectorR().Length() > 0 && InputMgr::GetInstance().AnalogPadVectorL().Length() > 0)change(PlayerState_Enum_Union::MOVE_BOTH);
	else if (holdable_padR()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
	else if (holdable_padL()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
}

// �ړ�����
void PlayerState_MoveEach::move(float deltaTime) {
	// butty�ɏd�͂��|����
	butty_->position() += gravity(deltaTime) * butty_->velocity();
	// retty�ɏd�͂��|����
	retty_->position() += gravity(deltaTime) * retty_->velocity();

	// butty�̒ǐՌv�Z
	if (element_.type_ == ActionType::Right) chase(retty_->position(), PLAYER_CNTR_DIV_NUM - 1);
	// retty�̒ǐՌv�Z
	if (element_.type_ == ActionType::Left)  chase(butty_->position(), 0);
	
	// butty�̈ړ�����
	butty_->position() = clamp(butty_->position(), 0);
	// retty�̈ړ�����
	retty_->position() = clamp(retty_->position(), PLAYER_CNTR_DIV_NUM - 1);
}

void PlayerState_MoveEach::flip_animation() {
	if (manuBody_->getPosition().x > autoBody_->getPosition().x) {
		autoBody_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	}
	else {
		autoBody_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);
	}
}

