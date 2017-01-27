#ifndef ROCK_H_
#define ROCK_H_

#include "../../Base/Actor.h"
#include "../../../Animation/Enemy/EnemyAnimation2D.h"

class Rock : public Actor {
private:
	enum class State {
		Idel,
		Fall,
		Dead
	};

public:
	Rock(IWorld* world, const Vector2&  position, const float bodyScale = 64.0f);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

private:
	// 状態の変更
	void changeState(State state);
	// 待機状態
	void idel(float deltaTime);
	// 落下状態
	void fall(float deltaTime);
	// 死亡状態
	void deadMove(float deltaTime);

private:
	float speed_;	// 速度
	float timer_;	// 時間
	State state_;	// 状態
	int animeNum_;
	EnemyAnimation2D animation_;
};

#endif
