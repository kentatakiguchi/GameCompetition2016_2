#include "PlayerState_HoldBase_Air.h"

#include "../../../../../../../../../Define.h"

// �R���X�g���N�^
PlayerState_HoldBase_Air::PlayerState_HoldBase_Air(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_HoldBase(butty, retty) {}

// �X�V����	
void PlayerState_HoldBase_Air::onUpdate(float deltaTime) {
	// �L�ы�ɂ���ď�Ԃ�J��
	if (moveBody_->distance() < PLAYER_SWIM_LENGTH) change(PlayerState_Enum_Union::HOLD_AIR, element_.type_);
	else if (moveBody_->distance() < PLAYER_MAX_STRETCH_LENGTH * 0.7f) change(PlayerState_Enum_Union::HOLD_AIR_SWIM, element_.type_);
	else change(PlayerState_Enum_Union::HOLD_AIR_FULL, element_.type_);
}

// �ړ�����
void PlayerState_HoldBase_Air::onMove(float deltaTime){
	// ���ꂼ���Body�ɏd�͂�������
	moveBody_->position() += gravity(deltaTime) / 2 * moveBody_->velocity();
	holdBody_->position() += gravity(deltaTime) / 2 * holdBody_->velocity();
}
