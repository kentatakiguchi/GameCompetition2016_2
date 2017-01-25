#pragma once

// �v���C���[�̃X�e�[�g�ꗗ
enum class PlayerState_Enum_Union {
	DAMMY,
	STAND_BY,
	IDLE,
	MOVE,
	MOVE_BOTH,
	HOLD,
	HOLD_BOTH,
	HOLD_AIR,
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
	JUMP,
	DEAD,
	LEAN_BACK
};