#include "PlayerStateMgr_Single.h"

#include "StatePath_Single.h"

#include "../../PlayerState_Enum.h"

// �R���X�g���N�^
PlayerStateMgr_Single::PlayerStateMgr_Single(const std::string& name){
	// �e�v���C���[�̃L�[�̓o�^
	PlayerState_Single::Keys keys;
	if (name == "PlayerBody1")keys = PlayerState_Single::Keys(KeyCode::UP, KeyCode::DOWN, KeyCode::RIGHT, KeyCode::LEFT);
	if (name == "PlayerBody2")keys = PlayerState_Single::Keys(KeyCode::W, KeyCode::S, KeyCode::D, KeyCode::A);

	// �e�X�e�[�g�̒ǉ�
	add(PlayerState_Enum_Single::STAND_BY, std::make_shared<PlayerState_Single_StandBy>(keys));
	add(PlayerState_Enum_Single::LEAN_BACK, std::make_shared<PlayerState_Single_LeanBack>(keys));
	add(PlayerState_Enum_Single::IDLE, std::make_shared<PlayerState_Single_Idle>(keys));
	add(PlayerState_Enum_Single::DEAD, std::make_shared<PlayerState_Single_Dead>(keys));
}

// ���݂̃X�e�[�g
bool PlayerStateMgr_Single::get_state(const PlayerState_Enum_Single & id){
	return currentState(static_cast<int>(id));
}

