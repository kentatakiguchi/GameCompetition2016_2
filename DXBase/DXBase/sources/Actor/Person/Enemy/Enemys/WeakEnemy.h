#ifndef WEAK_ENEMY_H_
#define WEAK_ENEMY_H_

#include "../BaseEnemy.h"

// デバッグ用エネミー
class WeakEnemy : public BaseEnemy {
public:
	WeakEnemy(IWorld * world, const Vector2& position);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

private:
	//// プレイヤーとの距離が短いときの行動です
	//void shortDistanceAttack();
	//// プレイヤーとの距離が中間の行動です
	//void centerDistanceAttack();
	//// プレイヤーとの距離が長いときの行動です
	//void longDistanceAttack();
	// 攻撃行動です
	void attack() override;
	//// 被弾行動です
	//void damageMove();
	//// 死亡行動です
	//void deadMove();
	// 索敵時の行動です
	void searchMove() override;
	// 追跡時の行動です
	void chaseMove() override;
};

#endif
