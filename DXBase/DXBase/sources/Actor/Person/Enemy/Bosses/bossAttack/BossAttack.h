#ifndef BOSS_ATTACK_H_
#define BOSS_ATTACK_H_

#include "../../../../../Math/Math.h"
#include "../../../../../Define.h"

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
	virtual Vector2 getMovePosition();
	// 攻撃行動のリフレッシュを行います
	virtual void Refresh();
	// 攻撃が終了したかを返します
	bool isAttackEnd();

	//// ジャンプ攻撃
	//void jumpAttack(float deltaTime);
	//// 壁攻撃
	//void wallAttack(float deltaTime);

protected:
	float timer_;		// 時間
	bool isAttackEnd_;	// 攻撃が終わったか
	Vector2 position_;	// 位置
};

#endif
