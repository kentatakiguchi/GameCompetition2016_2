#ifndef BOSS_HEART_H_
#define BOSS_HEART_H_

#include "../../../Base/Actor.h"
#include "../../../../Animation/Animation2D.h"
#include "../../../../World/IWorld.h"
#include "../../../../Math/Math.h"
#include "../../../../Define.h"

// ボス心臓クラス
class BossHeart : public Actor {
public:
	BossHeart(IWorld* world, const Vector2&  position, const int hp, const int bossHp);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

public:
	// 心臓の体力を返します
	int getHeartHp();
	// ボスの体力を返します
	int getBossHp();
	// プレイヤーが体内に入ったかを設定します
	void setIsEntered(bool isEntered);
	// プレイヤーを追い出したかを返します
	bool isLetOut();

private:
	// ステータスの初期化を行います
	void initStatus();

private:
	int stateCount_;		// 状態の個数
	int initStateCount_;	// 状態の個数(初期値)
	int hp_;				// 体力
	int initHp_;			// 体力(初期値)
	int prevHp_;			// 体力(前回の体力)
	int bossHp_;			// ボスの体力
	float timer_;			// 時間
	bool isEntered_;		// プレイヤーが入ってきたか
	bool isLetOut_;			// プレイヤーを追い出したか
};

#endif
