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
	// コンストラクタ
	virtual ~StateMgr();
public:
	// 更新処理
	void action(Actor& actor, float deltaTime) ;
	// 衝突処理
	void collide(const Actor & other);
	// 描画処理
	void draw()const;
	// 現在のステート
	bool currentState(const int& state = 0)const;
	// 現在のステート
	bool currentActionType(const ActionType& type = ActionType::None);
	// 現在の状態の要素
	IState::StateElement currentElement();
protected:
	// ステートの追加
	void addState(const int& id, const IStatePtr& state);
	// ステートの変更処理
	void changeState(Actor& actor, const IState::StateElement& element);
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
