#ifndef BOSS_MANAGER_H_
#define BOSS_MANAGER_H_

#include "bossAttack/BossAttack.h"
#include "../../../../Math/Math.h"
#include <vector>
#include <memory>

// class BossAttack;

class BossManager {
public:
	BossManager();
	// コンストラクタ
	BossManager(const Vector2& position);
	// 指定した番号の攻撃行動を行います
	void attackMove(const float number, const float deltaTime);
	// 行動のリフレッシュを行います
	void moveRefresh();
	// 行動によって移動した位置を返します
	Vector2 getMovePosition();
	// 攻撃が終了したかを返します
	bool isAttackEnd();

public:
	// 指定したオブジェクトとの方向を単位ベクトルで取得します
	Vector2 getDirection(const Vector2& otherPosition);
	// プレイヤーとの方向を単位ベクトルで取得します
	Vector2 getPlayerDirection();

private:
	int attackNumber_;		// 攻撃番号
	//float timer_;			// 時間
	//bool isAttackEnd_;		// 攻撃が終了しているか

	// ボス攻撃コンテナ
	typedef std::vector<std::shared_ptr<BossAttack>> BossAttackContainer;
	BossAttackContainer bossAttackContainer_;
};

#endif
