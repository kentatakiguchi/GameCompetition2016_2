#include "PlayerAnimation2D.h"

PlayerAnimation2D::PlayerAnimation2D(){

}

void PlayerAnimation2D::add(PlayerAnimID id, int res, int size, int row, int column, int surplus){
	for (int i = 0; i < column; ++i) {
		for (int j = 0; j < ((i < column - 1)? row : row - surplus); ++j) {
			// Ø‚èŽæ‚é¶ã‚ÌÀ•W
			Vector2 src = Vector2(row * size * j, column * size * i);
			sprites_[static_cast<int>(id)].push_back(DerivationGraph(src.x, src.y, size, size, res));
		}
	}
}

void PlayerAnimation2D::change(PlayerAnimID anim_id, float speed){
	change_param(static_cast<int>(anim_id), speed);
}
