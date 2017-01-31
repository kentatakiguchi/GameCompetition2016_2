#include "PlayerState_MoveEach.h"

// �R���X�g���N�^
PlayerState_MoveEach::PlayerState_MoveEach(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty) : PlayerState_Union(butty, retty) {}

// ��ԌŗL�̏�����
void PlayerState_MoveEach::unique_init(){
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

// �L�[���͏���
void PlayerState_MoveEach::key_input(float deltaTime){
	// butty�̓��͂ɂ�锽�]����
	if (InputMgr::GetInstance().KeyVector_R().x > 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().KeyVector_R().x < 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	// retty�̓��͂ɂ�锽�]����
	if (InputMgr::GetInstance().KeyVector_L().x > 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().KeyVector_L().x < 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	// ���͂ɂ��ړ�����
	if (element_.type_ == ActionType::Right) butty_->position() += InputMgr::GetInstance().KeyVector_R().Horizontal() * PLAYER_SPEED * butty_->velocity() * deltaTime * static_cast<float>(GetRefreshRate());
	if (element_.type_ == ActionType::Left)  retty_->position() += InputMgr::GetInstance().KeyVector_L().Horizontal() * PLAYER_SPEED * retty_->velocity() * deltaTime * static_cast<float>(GetRefreshRate());

	// �W�����v����
	if (jump_key()) change(PlayerState_Enum_Union::JUMP);
	// �ړ����͂��Ȃ��ꍇIDLE�ɕύX
	else if (!move_keyR() && !move_keyL()) change(PlayerState_Enum_Union::IDLE);
	// ���ړ��L�[�����͂��ꂽ�ꍇ��Ԃ�MOVE_BOTH�ɕύX
	else if (element_.type_ == ActionType::Right && move_keyL()) change(PlayerState_Enum_Union::MOVE_BOTH);
	else if (element_.type_ == ActionType::Left  && move_keyR()) change(PlayerState_Enum_Union::MOVE_BOTH);
	else if (holdable_keyR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	else if (holdable_keyL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
}

// �p�b�h���͏���
void PlayerState_MoveEach::pad_input(float deltaTime){
	// butty�̓��͂ɂ�锽�]����
	if (InputMgr::GetInstance().AnalogPadVectorR().x > 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().AnalogPadVectorR().x < 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	// retty�̓��͂ɂ�锽�]����
	if (InputMgr::GetInstance().AnalogPadVectorL().x > 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().AnalogPadVectorL().x < 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	// ���͂ɂ��ړ�����
	if (element_.type_ == ActionType::Right) butty_->position() += InputMgr::GetInstance().AnalogPadVectorR().Horizontal() * PLAYER_SPEED * butty_->velocity() * deltaTime * static_cast<float>(GetRefreshRate());;
	if (element_.type_ == ActionType::Left)  retty_->position() += InputMgr::GetInstance().AnalogPadVectorL().Horizontal() * PLAYER_SPEED * retty_->velocity() * deltaTime * static_cast<float>(GetRefreshRate());;
	
	// �W�����v����
	if (jump_pad()) change(PlayerState_Enum_Union::JUMP);
	// �ړ����͂��Ȃ��ꍇIDLE�ɕύX
	else if (!move_padR() && !move_padL()) change(PlayerState_Enum_Union::IDLE);
	// ���ړ��X�e�B�b�N�����͂��ꂽ�ꍇ��Ԃ�MOVE_BOTH�ɕύX
	else if (element_.type_ == ActionType::Right && move_padL()) change(PlayerState_Enum_Union::MOVE_BOTH);
	else if (element_.type_ == ActionType::Left  && move_padR()) change(PlayerState_Enum_Union::MOVE_BOTH);
	else if (holdable_padR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	else if (holdable_padL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
}

// �ړ�����
void PlayerState_MoveEach::move(float deltaTime) {
	// �d�͂̌v�Z
	Vector2 gravity = Vector2::Up * GRAVITY * deltaTime * static_cast<float>(GetRefreshRate());;
	// butty�ɏd�͂��|����
	butty_->position() += gravity * butty_->velocity();
	// retty�ɏd�͂��|����
	retty_->position() += gravity * retty_->velocity();

	// butty�̒ǐՌv�Z
	if (element_.type_ == ActionType::Right) chase(retty_->position(), PLAYER_CNTR_DIV_NUM - 1);
	// retty�̒ǐՌv�Z
	if (element_.type_ == ActionType::Left)  chase(butty_->position(), 0);
	
	// butty�̈ړ�����
	butty_->position() = clamp(butty_->position(), 0);
	// retty�̈ړ�����
	retty_->position() = clamp(retty_->position(), PLAYER_CNTR_DIV_NUM - 1);
}

void PlayerState_MoveEach::flip_animation(){
	if (element_.type_ == ActionType::Right) {
		if (butty_->getPosition().x > retty_->getPosition().x) {
			retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
		}
		else {
			retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);
		}
	}
	if (element_.type_ == ActionType::Left) {
		if (butty_->getPosition().x > retty_->getPosition().x) {
			butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);
		}
		else {
			butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
		}
	}
}
