#pragma once

#include "IState.h"

class State_Dammy : public IState {
public:
	State_Dammy(){}

	// 全てのステートに共通する初期化処理
	virtual void common_init(Actor & actor, ActionType type) override;
	// ステートの変更処理
	virtual void change(StateElement element) override;
	// ステートが終了したか否か
	virtual bool isEnd() override;
	// 次のステートの要素
	virtual StateElement next() const override;
};
