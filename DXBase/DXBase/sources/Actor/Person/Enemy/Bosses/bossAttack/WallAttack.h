#ifndef WALL_ATTACK_H_
#define WALL_ATTACK_H_

#include "BossAttack.h"

class WallAttack : public BossAttack {
private:
	enum class State {
		FloorSearch,
		FloorGetOff,
		WallMove,
		WallAttack
	};

public:
	WallAttack();
	WallAttack(const Vector2& position, const float heartHp);
	// 攻撃
	void attack(float deltaTime) override;
	// 攻撃行動のリフレッシュを行います
	virtual void Refresh() override;

private:
	// 床捜索状態です
	void floorSearch(float deltaTime);
	// 床から降りる状態です
	void floorGetOff(float deltaTime);
	// 壁移動状態です
	void wallMove(float deltaTime);
	// 壁攻撃状態です
	void wallAttack(float deltaTime);
	// 状態の変更を行います
	void changeState(State state);

private:
	int hp_;		// ボスの体力(心臓の体力)
	State state_;	// 状態
};

#endif
