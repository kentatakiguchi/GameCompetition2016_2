#pragma once

// プレイヤーのステート一覧
enum class PlayerState_Enum_Union {
	DAMMY,
	STAND_BY,
	IDLE,
	MOVE,
	MOVE_BOTH,
	HOLD,
	HOLD_BOTH,
	JUMP,
	ATTACK, 
	FREEZE
};

// プレイヤーのステート一覧
enum class PlayerState_Enum_Single {
	DAMMY,
	STAND_BY,
	IDLE,
	MOVE,
	JUMP,
	DEAD,
	LEAN_BACK
};