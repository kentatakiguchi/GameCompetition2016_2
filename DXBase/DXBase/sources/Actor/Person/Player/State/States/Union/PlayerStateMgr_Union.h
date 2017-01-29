#pragma once

#include "../../Base/StateMgr.h"
#include "../../PlayerState_Enum.h"

#include "../../../PlayerPtr.h"

// �X�e�[�g�̏����Ǘ�
class PlayerStateMgr_Union : public StateMgr {
public:
	// �R���X�g���N�^
	PlayerStateMgr_Union(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
	// �X�e�[�g�̒ǉ�
	void add(const PlayerState_Enum_Union& id, const IStatePtr& state);
	// �X�e�[�g�̕ύX����
	void change(Actor& actor, const PlayerState_Enum_Union& id, const ActionType& type = ActionType::None);
	// ���݂̃X�e�[�g
	bool get_state(const PlayerState_Enum_Union& id);
};