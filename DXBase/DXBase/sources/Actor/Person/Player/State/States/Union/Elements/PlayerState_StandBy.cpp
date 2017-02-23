#include "PlayerState_StandBy.h"

// �R���X�g���N�^
PlayerState_StandBy::PlayerState_StandBy(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty) : PlayerState_Union(butty, retty) {}

// ��ԌŗL�̏�����
void PlayerState_StandBy::unique_init(){
	// �e�v���C���[�̏�Ԃ�������ԂɕύX
	butty_->change_state(PlayerState_Enum_Single::STAND_BY);
	retty_->change_state(PlayerState_Enum_Single::STAND_BY);

	// �ҋ@��ԂɑJ��
	change(PlayerState_Enum_Union::IDLE);
}


