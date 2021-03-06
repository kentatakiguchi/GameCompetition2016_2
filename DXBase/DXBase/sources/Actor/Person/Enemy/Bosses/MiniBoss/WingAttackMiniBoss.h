#ifndef WING_ATTACK_MINI_BOSS_H_
#define WING_ATTACK_MINI_BOSS_H_

#include "FighterMiniBossh.h"
#include <map>
#include <random>

class WingAttackMiniBoss : public FighterMiniBoss {
public:
	WingAttackMiniBoss(
		IWorld* world,
		const Vector2&  position,
		const float bodyScale = 64.0f);
	/*void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;*/

private:
	// 待機状態
	void idel(float deltaTime) override;
	// 移動状態
	void move(float deltaTime) override;
	//  
	void attack(float deltaTime) override;
	// 死亡状態
	void deadMove(float deltaTime) override;
	// アニメーションの追加
	void addAnimation() override;
	// 羽攻撃
	void wingAttack();

private:
	int attackCount_;			// 攻撃回数
	bool isAttack_;				// 攻撃したか
	Vector2 direction_;			// 方向
	std::mt19937 mt_;			// 乱数の初期seed
	// 羽の回転コンテナ
	typedef std::map<int, float> WingDegreeMap;
	WingDegreeMap wingDegrees;
};

#endif