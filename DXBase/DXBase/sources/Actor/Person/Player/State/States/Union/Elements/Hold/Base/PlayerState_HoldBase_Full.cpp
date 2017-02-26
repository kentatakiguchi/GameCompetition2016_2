#include "PlayerState_HoldBase_Full.h"

#include "../../../../../../../../../Input/InputMgr.h"

#include "../../../../../../Effect/PlayerEffectObj.h"
#include "../../../../../../../../Base/ActorGroup.h"

// �R���X�g���N�^
PlayerState_HoldBase_Full::PlayerState_HoldBase_Full(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_HoldBase(butty, retty) {}

// ��ԌŗL�̏�����
void PlayerState_HoldBase_Full::onInit(){
	// �`���[�W�G�t�F�N�g�̐���
	cntr_->world_->addActor(ActorGroup::Effect, std::make_shared<PlayerEffectObj>(cntr_->world_, cntr_->getPosition(), PlayerEffectID::SHOUGEKI, 3.0f, 5.0f));
	
	// �`���[�W���ʉ��̍Đ�
	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_NOBI_FULL), DX_PLAYTYPE_BACK);
}

// �I��������
void PlayerState_HoldBase_Full::onEnd(){}

// �p�b�h���͏���
void PlayerState_HoldBase_Full::onInput(float deltaTime){
	// �������{�^�������ꂽ�ꍇAttack��ԂɑJ��
	if (hold_released()) change(PlayerState_Enum_Union::ATTACK, element_.type_);
}

