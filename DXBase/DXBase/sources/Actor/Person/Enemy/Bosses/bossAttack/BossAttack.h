#ifndef BOSS_ATTACK_H_
#define BOSS_ATTACK_H_

#include "../../../../../Math/Math.h"
#include "../../../../../Define.h"

// ボス攻撃クラス(ベース)
class BossAttack {
public:
	BossAttack();
	BossAttack(const Vector2& position);
	// デストラクタ
	virtual ~BossAttack();
	// 更新
	void update(float deltaTime);
	// 攻撃
	virtual void attack(float deltaTime);
	// 移動した位置を取得します
	Vector2 getMovePosition();
	// 攻撃行動のリフレッシュを行います
	virtual void Refresh();
	// 攻撃が終了したかを返します
	bool isAttackEnd();

public:
	// 位置を設定します
	void setPosition(const Vector2& position);
	// プレイヤーとの方向を設定します
	void setDirection(const Vector2& direction);
	// 床に触れているかを設定します
	void setIsGround(bool isGround);

protected:
	float timer_;		// 時間
	bool isAttackEnd_;	// 攻撃が終わったか
	bool isGround_;		// ボスが床に触れているのか
	Vector2 position_;	// 位置
	Vector2 direction_;	// プレイヤーとの方向
};

#endif
