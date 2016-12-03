#pragma once

#include "../Base/Animation2D.h"

#include <unordered_map>

enum class PlayerAnimID {
	NONE,
	IDLE,
	MOVE,
	HOLD,
	SWIM,	
	DEATH,
	DAMAGE,
	DIV_IDLE,
	DIV_MOVE,
	TURN,
	SWIM_TURN,
	COUNT
};


class PlayerAnimation2D : public Animation2D{
public:
	// コンストラクタ
	PlayerAnimation2D();
	void add(PlayerAnimID id, int res, int size, int row, int column, int surplus);
	void change(PlayerAnimID anim_id, float speed = 1.0f);
	void change_dir(ActionType type);
};
