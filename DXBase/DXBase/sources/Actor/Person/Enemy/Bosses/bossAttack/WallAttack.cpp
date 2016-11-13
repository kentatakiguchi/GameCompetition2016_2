#include "WallAttack.h"

WallAttack::WallAttack() :
	BossAttack(Vector2::Zero),
	hp_(0),
	state_(State::FloorSearch)
{
}

WallAttack::WallAttack(const Vector2 & position, const float heartHp) :
	BossAttack(position),
	hp_(heartHp),
	state_(State::FloorSearch)
{
}

void WallAttack::attack(float deltaTime)
{
	switch (state_)
	{
	case State::FloorSearch: floorSearch(deltaTime); break;
	case State::FloorGetOff: floorGetOff(deltaTime); break;
	case State::WallMove: wallMove(deltaTime); break;
	case State::WallAttack: wallAttack(deltaTime); break;
	}
}

void WallAttack::Refresh()
{
	BossAttack::Refresh();
}

// 床捜索状態です
void WallAttack::floorSearch(float deltaTime)
{
	// 浮いている床に接地していれば、床を降りる	
	// そうでなければ、壁移動に遷移
}

// 床から降りる状態です
void WallAttack::floorGetOff(float deltaTime)
{
	// ボスの位置と床の中心位置を参照して、
	// 計算して出てきた方向をかけて移動する
	// 普通の床に接地したら壁移動に遷移
}

// 壁移動状態です
void WallAttack::wallMove(float deltaTime)
{
	// 時計周りで移動
	// 一定時間経過で、壁攻撃に遷移
}

// 壁攻撃状態です
void WallAttack::wallAttack(float deltaTime)
{
	// プレイヤーの居た位置に向かって飛ぶ
}

// 状態の変更を行います
void WallAttack::changeState(State state)
{
	state_ = state;
	timer_ = 0.0f;
}
