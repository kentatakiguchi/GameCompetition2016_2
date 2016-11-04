#ifndef FLYING_ENEMY_H_
#define FLYING_ENEMY_H_

#include "../BaseEnemy.h"

class FloorSearchPoint;

class FlyingEnemy : public BaseEnemy {
public:
	FlyingEnemy(IWorld * world, const Vector2& position);
	void onUpdate(float deltaTime) override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

private:
	// プレイヤーを発見した時の行動です
	void discovery();
	// 攻撃行動です
	void attack();
	// 索敵時の行動です
	void searchMove();
	// 追跡時の行動です
	void chaseMove();
	// 
	void lostMove();

private:
	float direTimer_;			// 方向転換する時間
	float lostTimer_;			// 見失った時間
	Vector2 pastPosition;
	FloorSearchPoint* wsObj_;	// 壁捜索オブジェクト
};

#endif
