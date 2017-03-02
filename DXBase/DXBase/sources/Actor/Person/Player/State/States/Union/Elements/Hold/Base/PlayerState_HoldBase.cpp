#include "PlayerState_HoldBase.h"

#include "../../../../../../../../../Define.h"
#include "../../../../../../../../../Input/InputMgr.h"
#include "../../../../../../../../../Scene/Base/SceneDataKeeper.h"

// �R���X�g���N�^
PlayerState_HoldBase::PlayerState_HoldBase(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_Union(butty, retty) {}

// ��ԌŗL�̏�����
void PlayerState_HoldBase::unique_init(){
	// �������Ă���v���C���[�ƈړ����Ă���v���C���[�̐ݒ�
	//retty���������Ă���ꍇ
	if (element_.type_ == ActionType::Right) {
		holdBody_ = retty_;
		moveBody_ = butty_;
	}
	//butty���������Ă���ꍇ
	if (element_.type_ == ActionType::Left) {
		holdBody_ = butty_;
		moveBody_ = retty_;
	}

	// �p����̏���������	
	onInit();
}

// �X�V����	
void PlayerState_HoldBase::update(float deltaTime){
	// �`���[�W���ԃJ�E���g�X�V
	cntr_->getWorld()->GetKeeper()->addChargeTime(deltaTime);

	// �p����̍X�V����	
	onUpdate(deltaTime);

	// �ړ�����
	move(deltaTime);
}

// �I��������
void PlayerState_HoldBase::end(){
	// �p����̏I��������
	onEnd();
}

// ���͏���
void PlayerState_HoldBase::input(float deltaTime){
	// ���͂ɂ����W�ړ�
	moveBody_->position() += input_vector(InputMgr::GetInstance().PadVector(element_.type_), deltaTime);

	// ���͂ɂ��A�j���[�V�����؂�ւ�
	if (InputMgr::GetInstance().PadVector(element_.type_).x > 0) moveBody_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Right);
	if (InputMgr::GetInstance().PadVector(element_.type_).x < 0) moveBody_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Left);

	// �p����̓��͏���
	onInput(deltaTime);
}

// �ړ�����
void PlayerState_HoldBase::move(float deltaTime) {
	// �p����̈ړ�����
	onMove(deltaTime);


	// �v���C���[�̈ړ�����
	if (element_.type_ == ActionType::Right) {
		butty_->position() = clamp(butty_->position(), 0);
	}
	if (element_.type_ == ActionType::Left) {
		retty_->position() = clamp(retty_->position(), PLAYER_CNTR_DIV_NUM - 1);
	}

}

// �ړ����x�v�Z
Vector2 PlayerState_HoldBase::input_vector(const Vector2 & input, float deltaTime){
	return input * 7.5f * moveBody_->velocity() * PLAYER_SPEED * moveBody_->dump() * time(deltaTime);
}

// �������{�^�������ꂽ�ꍇ
bool PlayerState_HoldBase::hold_released() {
	// �������{�^�������ꂽ���ǂ���
	return	(!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Left) || 
			(!InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Right);
}




