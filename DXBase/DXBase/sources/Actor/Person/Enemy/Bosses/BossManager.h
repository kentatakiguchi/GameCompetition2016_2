#ifndef BOSS_MANAGER_H_
#define BOSS_MANAGER_H_

#include "bossAttack/BossAttack.h"
#include "../../../../Math/Math.h"
#include <vector>
#include <memory>

// class BossAttack;

// ボスマネージャー 
class BossManager {
public:
	BossManager();
	// コンストラクタ
	BossManager(const Vector2& position);
	// 指定した番号の攻撃行動を行います
	void attackMove(const float number, const float deltaTime);
	// 攻撃のリフレッシュを行います
	void attackRefresh();
	// 行動によって移動した位置を返します
	Vector2 getMovePosition();
	// 攻撃が終了したかを返します
	bool isAttackEnd();

public:
	// ボスの位置を設定します
	void setPosition(const Vector2& position);
	// プレイヤーの位置を設定します
	void setPlayerPosition(const Vector2& position);
	// 攻撃前の位置を決定します
	void prevPosition();
	// 指定したオブジェクトとの方向を単位ベクトルで取得します
	Vector2 getDirection(const Vector2& otherPosition);
	// プレイヤーとの方向を単位ベクトルで取得します
	Vector2 getPlayerDirection();
	// ボスが接地しているかを設定します
	void setIsGround(bool isGround);
	// ボスが壁の下側に当たったかを設定します
	void setIsBottom(bool isBottom);

private:
	int attackNumber_;			// 攻撃番号
	Vector2 bossPosition_;		// ボスの位置
	Vector2 playerPosition_;	// プレイヤーの位置
	//float timer_;			// 時間
	//bool isAttackEnd_;		// 攻撃が終了しているか

	// ボス攻撃コンテナ
	typedef std::vector<std::shared_ptr<BossAttack>> BossAttackContainer;
	BossAttackContainer bossAttackContainer_;
};

#endif
