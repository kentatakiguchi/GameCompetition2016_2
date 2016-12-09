#pragma once

#include "../../Base/StateMgr.h"
#include "../../PlayerState_Enum.h"

// ステートの処理管理
class PlayerStateMgr_Union : public StateMgr {
public:
	// コンストラクタ
	PlayerStateMgr_Union();
	// ステートの追加
	void add(const PlayerState_Enum_Union& id, const IStatePtr& state);
	// ステートの変更処理
	void change(Actor& actor, const PlayerState_Enum_Union& id, const ActionType& type = ActionType::None);
	// 現在のステート
	bool get_state(const PlayerState_Enum_Union& id);
};