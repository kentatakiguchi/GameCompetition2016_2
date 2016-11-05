#pragma once

// プレイヤーのステート一覧
enum class PlayerState_Enum_Union {
	DAMMY,
	STAND_BY,
	IDLE,
	MOVE,
	HOLD,
	HOLD_BOTH,
	QUICK,
	JUMP,
	SPLIT,
	ATTACK, 
	ATTACK2,
	DAMAGE
};

// プレイヤーのステート一覧
enum class PlayerState_Enum_Single {
	DAMMY,
	STAND_BY,
	IDLE,
	MOVE,
	HOLD,
	HOLD_BOTH,
	QUICK,
	JUMP,
	SPLIT,
	ATTACK,
	ATTACK2,
	DAMAGE
};