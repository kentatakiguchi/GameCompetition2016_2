#pragma once

#include "../../Base/StateMgr.h"

// ��s�錾
enum class PlayerState_Enum_Single;

// �������̃X�e�[�g�Ǘ�
class PlayerStateMgr_Single : public StateMgr {
public:
	// �R���X�g���N�^
	PlayerStateMgr_Single(const std::string& name = "");
	// ���݂̃X�e�[�g
	bool get_state(const PlayerState_Enum_Single& id);
};