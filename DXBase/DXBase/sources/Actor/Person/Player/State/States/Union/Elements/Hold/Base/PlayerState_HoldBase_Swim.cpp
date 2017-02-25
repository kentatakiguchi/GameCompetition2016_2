#include "PlayerState_HoldBase_Swim.h"

#include "../../../../../../../../../Input/InputMgr.h"

// �R���X�g���N�^
PlayerState_HoldBase_Swim::PlayerState_HoldBase_Swim(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_HoldBase(butty, retty) {}

// ��ԌŗL�̏�����
void PlayerState_HoldBase_Swim::onInit(){
	// �������ړ������ʉ��Đ�
	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_NOBI), DX_PLAYTYPE_LOOP);
}

// �I��������
void PlayerState_HoldBase_Swim::onEnd(){
	// �������ړ������ʉ���~
	StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_NOBI));
}

// �p�b�h���͏���
void PlayerState_HoldBase_Swim::onInput(float deltaTime){
	// �������{�^�������ꂽ�ꍇIDLE��ԂɑJ��
	if (hold_released()) change(PlayerState_Enum_Union::IDLE);
}
