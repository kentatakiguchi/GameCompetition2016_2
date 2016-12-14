#pragma once

#include "../Base/Animation2D.h"

#include <unordered_map>

enum class PlayerEffectID {
	NONE,
	SEP_EXP,
	SEP_MOVE,
	COUNT
};

class PlayerEffect2D : public Animation2D {
public:
	PlayerEffect2D();
	void add(const PlayerEffectID & id, const int & res, const int & size, const int & row, const int & column, const int & surplus);
	void change(const PlayerEffectID& id, const float& speed = 1.0f);
};
