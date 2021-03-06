#ifndef ROCK_H_
#define ROCK_H_

#include "Bosses/MiniBoss/AdhereMiniBoss.h"

class Rock : public AdhereMiniBoss {
public:
	Rock(IWorld* world, const Vector2&  position, const float bodyScale = 64.0f);

private:
	// 落下状態
	void move(float deltaTime) override;
	// 死亡状態
	void deadMove(float deltaTime) override;
	// 床に当たった時の処理
	void floorHit() override;
};

#endif
