#include "PlayerState_HoldBase_Begin.h"

#include "../../../../../../../../../Input/InputMgr.h"

// �R���X�g���N�^
PlayerState_HoldBase_Begin::PlayerState_HoldBase_Begin(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_HoldBase(butty, retty) {}

// ��ԌŗL�̏�����
void PlayerState_HoldBase_Begin::onInit(){
	// �A�j���[�V�����̑J��
	moveBody_->animation().change(PlayerAnimID::SWIM);
	holdBody_->animation().change(PlayerAnimID::HOLD);

	//// �����������ʉ��Đ�
	//PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_SYOUTOTU), DX_PLAYTYPE_BACK);
}

// �I��������
void PlayerState_HoldBase_Begin::onEnd(){}

// �p�b�h���͏���
void PlayerState_HoldBase_Begin::onInput(float deltaTime){
	// �������{�^�������ꂽ�ꍇIDLE��ԂɑJ��
	if (hold_released()) change(PlayerState_Enum_Union::IDLE);
}
