#pragma once

#include "IState.h"

class State_Dammy : public IState {
public:
	// コンストラクタ
	State_Dammy(){}
	// 全てのステートに共通する初期化処理
	virtual void common_init(Actor& actor, const ActionType& type) override {}
	// 入力処理
	virtual void input(float deltaTime) override {}
	// ステートの変更処理
	virtual void change(const StateElement& element) override {}
	// ステートが終了したか否か
	virtual bool isEnd() override { return false; }
	// 次のステートの要素
	virtual StateElement next() const override { return StateElement(-1); }

	virtual void unique_init() override{}

	virtual void update(float deltaTime) override {}
	
	virtual void common_update(float deltaTime) override {}

	virtual void end() override {}
};
