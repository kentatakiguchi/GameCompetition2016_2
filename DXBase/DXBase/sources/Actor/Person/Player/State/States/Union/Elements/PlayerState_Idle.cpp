#include "PlayerState_Idle.h"

#include "../../../../../../../Define.h"
#include "../../../../../../../Scene/Base/SceneDataKeeper.h"

// �R���X�g���N�^
PlayerState_Idle::PlayerState_Idle(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty) : PlayerState_Union(butty, retty) {}

// ��ԌŗL�̏�����
void PlayerState_Idle::unique_init(){
	// butty�̃A�j���[�V������IDLE�ɕύX
	butty_->animation().change(PlayerAnimID::IDLE);
	// retty�̃A�j���[�V������IDLE�ɕύX
	retty_->animation().change(PlayerAnimID::IDLE);

	//cntr_->getWorld()->GetKeeper()->setJumpCount(0);
	cntr_->getWorld()->GetKeeper()->comboReset(0);
}

// �X�V����
void PlayerState_Idle::update(float deltaTime) {
	// �ړ�����
	move(deltaTime);

	// �{�X�X�e�[�W��p�C�x���g����Event��ԂɕύX
	if (cntr_->getWorld()->isEntered()) change(PlayerState_Enum_Union::EVENT);
}

// �I��������
void PlayerState_Idle::end(){}

// ���͏���
void PlayerState_Idle::input(float deltaTime){
	// �W�����v�{�^�����͎��ɃW�����v��ԂɕύX
	if (jump_pad()) change(PlayerState_Enum_Union::JUMP);

	// �E�X�e�B�b�N���͎���butty�ړ���ԂɕύX
	else if (move_padR()) change(PlayerState_Enum_Union::MOVE, ActionType::Right);
	// ���X�e�B�b�N���͎���butty�ړ���ԂɕύX
	else if (move_padL()) change(PlayerState_Enum_Union::MOVE, ActionType::Left);

	// butty�������\����R1�{�^���ł�������ԂɕύX
	else if (holdable_padR()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
	// retty�������\����R1�{�^���ł�������ԂɕύX
	else if (holdable_padL()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
}

// �ړ�����
void PlayerState_Idle::move(float deltaTime) {
	// butty�ɏd�͂��|����
	butty_->position() += gravity(deltaTime) * butty_->velocity();
	// retty�ɏd�͂��|����
	retty_->position() += gravity(deltaTime) * retty_->velocity();

	// butty�̒ǐՌv�Z
	chase(butty_->position(), 0);
	// retty�̒ǐՌv�Z
	chase(retty_->position(), PLAYER_CNTR_DIV_NUM - 1);

	//if (!cntr_->getWorld()->GetPlayerNotMove()) {
		// butty�̈ړ�����
		butty_->position() = clamp(butty_->position(), 0);
		// retty�̈ړ�����
		retty_->position() = clamp(retty_->position(), PLAYER_CNTR_DIV_NUM - 1);
	//}
}



