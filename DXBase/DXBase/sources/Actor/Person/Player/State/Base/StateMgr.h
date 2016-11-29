#pragma once

#include "IStatePtr.h"
#include "IState.h"
#include "../../../../Base/Actor.h"
#include <unordered_map>

// ステートの処理管理
class StateMgr{
public:
	// コンストラクタ
	StateMgr();
public:
	// 更新処理
	void action(Actor& actor, float deltaTime) ;
	// ステートの変更処理
	void changeState(Actor& actor, IState::StateElement element);
	// ステートの追加
	void add(unsigned int state, const IStatePtr& scene);
	// 現在のステート
	bool currentState(unsigned int state = 0);
	// 現在のステート
	bool currentActionType(ActionType action_type = ActionType::None);
	// 現在の状態の要素
	IState::StateElement currentElement();
private:
	// コピー禁止
	StateMgr(const StateMgr& other) = delete;
	StateMgr& operator = (const StateMgr& other) = delete;
private:
	// ステート登録用map
	std::unordered_map<unsigned int, IStatePtr> states_;
	// 現在のステート
	IStatePtr currentState_;
	// 現在の要素
	IState::StateElement element_;
};
