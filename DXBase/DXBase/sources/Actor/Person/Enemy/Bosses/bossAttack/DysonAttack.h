#ifndef DYSON_ATTACK_H_
#define DYSON_ATTACK_H_

#include "BossAttack.h"

class IWorld;
class Tornado;

// 吸い込み攻撃
class DysonAttack : public BossAttack {
private:
	enum class State {
		Attack,
		Flinch,
		Fatigue
	};

public:
	DysonAttack();
	DysonAttack(IWorld* world, const Vector2& position);
	// 攻撃
	void attack(float deltaTime) override;
	// 攻撃行動のリフレッシュを行います
	void Refresh() override;

private:
	// 攻撃状態
	void dysonAttack(float deltaTime);
	// 怯み状態
	void flinch(float deltaTime);
	// 疲労状態
	void fatigue(float deltaTime);
	// 状態の変更を行います
	void changeState(State state, int num);

private:
	int windSE_;			// 吸い込み時のSE
	float addAngle_;		// 角度の加算量
	bool isRockCreate_;		// 岩を生成したか 

	Tornado* tornadoObj_;	// 竜巻オブジェクト

	State state_;
};

#endif
