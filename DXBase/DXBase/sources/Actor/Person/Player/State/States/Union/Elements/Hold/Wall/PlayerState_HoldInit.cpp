#include "PlayerState_HoldInit.h"

#include "../../../../../../../../../Define.h"
#include "../../../../../../../../../Input/InputMgr.h"
#include "../../../../../../../../../Scene/Base/SceneDataKeeper.h"
#include "../../../../../../PlayerBodyCollider.h"

PlayerState_HoldInit::PlayerState_HoldInit(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_HoldBase(butty, retty) {}

void PlayerState_HoldInit::onInit(){
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

	cntr_->getWorld()->GetKeeper()->addHoldCount(1);
}

void PlayerState_HoldInit::onUpdate(float deltaTime){
	change(PlayerState_Enum_Union::HOLD_BEGIN, element_.type_);
}

void PlayerState_HoldInit::onEnd(){}

void PlayerState_HoldInit::onKeyInput(float deltaTime){}

void PlayerState_HoldInit::onPadInput(float deltaTime){}

void PlayerState_HoldInit::onMove(float deltaTime){}
