#ifndef ROCK_H_
#define ROCK_H_

#include "../../Base/Actor.h"
#include "../../../Animation/Enemy/EnemyAnimation2D.h"

class Rock : public Actor {
private:
	enum class State {
		Idel,
		Fall,
		Adhere,
		Dead
	};
	// アニメーション番号
	enum {
		WAIT_NUMBER = 0,
		RUN_NUMBER = 1,
		ADHERE_NUMBER = 2,
		DEAD_NUMBER = 3
	};

public:
	Rock(IWorld* world, const Vector2&  position, const float bodyScale = 64.0f);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

private:
	// 状態の変更
	void changeState(State state, int animation);
	// 待機状態
	void idel(float deltaTime);
	// 落下状態
	void fall(float deltaTime);
	// くっつき状態
	void adhere(float deltaTime);
	// 死亡状態
	void deadMove(float deltaTime);

private:
	// プレイヤーとの方向を返します
	Vector2 getPlayerDirection();
	// テクスチャの位置を設定します
	void setTexPosition(float up);
	// アニメーションの追加
	void addAnimation();
	// ランダムの角度を取得します
	float getRandomDegree();

private:
	float speed_;					// 速度
	float timer_;					// 時間
	float size_;					// 大きさ
	float degree_;					// 角度
	std::string playerName_;		// プレイヤーの名前
	Vector2 texPos_;				// テクスチャの位置
	Vector2 orizin_;				// 中点
	State state_;					// 状態
	EnemyAnimation2D animation_;	// アニメーション
};

#endif
