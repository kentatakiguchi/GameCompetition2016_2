#ifndef WEAK_ENEMY_H_
#define WEAK_ENEMY_H_

#include "BaseEnemy.h"

class WeakEnemy : public BaseEnemy {
public:
	WeakEnemy(IWorld * world, const Vector3& position);
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;

private:
	// 待機状態です
	void idel();
	// 索敵移動します
	void searchMove();
	// プレイヤーを追跡します
	void chaseMove();
	//// プレイヤーとの距離が短いときの行動です
	//void shortDistanceAttack();
	//// プレイヤーとの距離が中間の行動です
	//void centerDistanceAttack();
	//// プレイヤーとの距離が長いときの行動です
	//void longDistanceAttack();
	// 攻撃行動です
	void Attack();
	//// 被弾行動です
	//void damageMove();
	//// 死亡行動です
	//void deadMove();
	//// 状態の変更を行います
	//void changeState(State state, unsigned int motion);
};

#endif
