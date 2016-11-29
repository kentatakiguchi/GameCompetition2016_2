#pragma once

//#include "StateMgr.h"
#include "../../../../../World/IWorld.h"
#include "../../../../Base/ActorGroup.h"
#include "ActionType.h"

class Actor;

class IState {
public:
	// ステートの要素
	struct StateElement {
		int state_;
		ActionType action_type_;

		// コンストラクタ
		StateElement(int state, ActionType action_type = ActionType::None){
			state_ = state;
			action_type_ = action_type;
		}
	};

public:
	// 仮想デストラクタ
	virtual ~IState() {}
	// 全状態共通の初期化
	virtual void common_init(Actor& actor, ActionType type = ActionType::None) = 0;
	// 各状態独自の初期化
	virtual void unique_init() = 0;
	// 入力処理
	virtual void input() = 0;
	// 更新処理
	virtual void update(float deltaTime) = 0;
	// 状態の変更
	virtual void change(StateElement element) = 0;
	// 終了を返す
	virtual bool isEnd() = 0;
	// 次のステートの要素
	virtual StateElement next() const = 0;
	// 終了時の処理
	virtual void end() = 0;
};
