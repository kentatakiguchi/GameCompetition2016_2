#pragma once

#include "../../Base/StateMgr.h"
#include "../../PlayerState_Enum.h"

// ステートの処理管理
class PlayerStateMgr_Single : public StateMgr {
public:
	// コンストラクタ
	PlayerStateMgr_Single(const std::string& name = "");
	// ステートの追加
	void add(const PlayerState_Enum_Single& id, const IStatePtr& state);
	// ステートの変更処理
	void change(Actor& actor, const PlayerState_Enum_Single& id, const ActionType& type = ActionType::None);
	// 現在のステート
	bool get_state(const PlayerState_Enum_Single& id);
};