#pragma once

#include "../../Base/StateMgr.h"
#include "../../PlayerState_Enum.h"

// �X�e�[�g�̏����Ǘ�
class PlayerStateMgr_Single : public StateMgr {
public:
	// �R���X�g���N�^
	PlayerStateMgr_Single(const std::string& name = "");
	// �X�e�[�g�̒ǉ�
	void add(const PlayerState_Enum_Single& id, const IStatePtr& state);
	// �X�e�[�g�̕ύX����
	void change(Actor& actor, const PlayerState_Enum_Single& id, const ActionType& type = ActionType::None);
	// ���݂̃X�e�[�g
	bool get_state(const PlayerState_Enum_Single& id);
};