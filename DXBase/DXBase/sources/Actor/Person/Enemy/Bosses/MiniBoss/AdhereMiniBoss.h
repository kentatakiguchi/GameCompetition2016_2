#ifndef ADHERE_MINI_BOSS_H_
#define ADHERE_MINI_BOSS_H_

//#include "../../../../Base/Actor.h"
#include "FighterMiniBossh.h"
#include "../../../../../Animation/Enemy/EnemyAnimation2D.h"

class AdhereMiniBoss : public FighterMiniBoss {
protected:
	/*enum class State {
		Idel,
		Move,
		Adhere,
		Dead
	};*/
	// 死亡状態
	enum class DeadState {
		HitDead,
		AdhereDead
	};
	//// アニメーション番号
	//enum {
	//	WAIT_NUMBER = 0,
	//	RUN_NUMBER = 1,
	//	ADHERE_NUMBER = 2,
	//	DEAD_NUMBER = 3
	//};

public:
	AdhereMiniBoss(
		IWorld* world, 
		const Vector2&  position, 
		const float bodyScale = 64.0f);
	/*void onUpdate(float deltaTime) override;
	void onDraw() const override;*/
	/*void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;*/

protected:
	// 状態の変更
	void changeDeadState(DeadState dState, int animation);
	//// 状態の更新
	//void updateState(float deltaTime);
	// 待機状態
	void idel(float deltaTime) override;
	// 移動状態
	virtual void move(float deltaTime) override;
	// くっつき状態
	virtual void attack(float deltaTime) override;
	// 死亡状態
	virtual void deadMove(float deltaTime) override;
	// くっつき死亡状態
	void adhereDead(float deltaTime);
	// 床に当たった時の処理
	virtual void floorHit() override;
	// プレイヤーと当たった時の処理
	void playerHit(Actor& actor) override;

protected:
	//// プレイヤーとの方向を返します(単位ベクトル)
	//Vector2 getPlayerDirection();
	//// テクスチャの位置を設定します
	//void setTexPosition(float up);
	//// アニメーションの追加
	virtual void addAnimation() override;
	// ランダムの角度を取得します
	float getRandomDegree();
	//// 地面の位置に補正します
	//void groundClamp(Actor& actor);

protected:
	float adhereDeadTime_;	// くっつき時の死亡時間
	DeadState dState_;		// 死亡状態
};

#endif

