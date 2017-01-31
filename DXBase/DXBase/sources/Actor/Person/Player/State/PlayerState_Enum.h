#pragma once

// �v���C���[�̃X�e�[�g�ꗗ
enum class PlayerState_Enum_Union {
	DAMMY,
	STAND_BY,
	IDLE,
	MOVE,
	MOVE_BOTH,
	HOLD,
	HOLD_SWIM,
	HOLD_FULL,
	HOLD_AIR,
	HOLD_AIR_SWIM,
	HOLD_AIR_FULL,
	HOLD_BOTH,
	JUMP,
	ATTACK,
	FREEZE,
	EVENT,
	LEAN_BACK
};

// �v���C���[�̃X�e�[�g�ꗗ
enum class PlayerState_Enum_Single {
	DAMMY,
	STAND_BY,
	IDLE,
	MOVE,
	DEAD,
	LEAN_BACK
};