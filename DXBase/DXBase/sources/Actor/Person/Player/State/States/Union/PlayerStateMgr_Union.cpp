#include "PlayerStateMgr_Union.h"

#include "StatePath_Union.h"

PlayerStateMgr_Union::PlayerStateMgr_Union(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty){
	add(PlayerState_Enum_Union::STAND_BY, std::make_shared<PlayerState_StandBy>(butty, retty));
	add(PlayerState_Enum_Union::IDLE, std::make_shared<PlayerState_Idle>(butty, retty));
	add(PlayerState_Enum_Union::MOVE, std::make_shared<PlayerState_MoveEach>(butty, retty));
	add(PlayerState_Enum_Union::MOVE_BOTH, std::make_shared<PlayerState_MoveBoth>(butty, retty));
	add(PlayerState_Enum_Union::JUMP, std::make_shared<PlayerState_Jump>(butty, retty));
	add(PlayerState_Enum_Union::HOLD, std::make_shared<PlayerState_Hold>(butty, retty));
	add(PlayerState_Enum_Union::HOLD_BOTH, std::make_shared<PlayerState_HoldBoth>(butty, retty));
	add(PlayerState_Enum_Union::HOLD_AIR, std::make_shared<PlayerState_HoldAir>(butty, retty));
	add(PlayerState_Enum_Union::ATTACK, std::make_shared<PlayerState_Attack>(butty, retty));
	add(PlayerState_Enum_Union::FREEZE, std::make_shared<PlayerState_Freeze>(butty, retty));
	add(PlayerState_Enum_Union::LEAN_BACK, std::make_shared<PlayerState_LeanBack>(butty, retty));
	add(PlayerState_Enum_Union::EVENT, std::make_shared<PlayerState_EventTime>(butty, retty));
}

void PlayerStateMgr_Union::add(const PlayerState_Enum_Union & id, const IStatePtr & state){
	addState(static_cast<int>(id), state);
}

void PlayerStateMgr_Union::change(Actor & actor, const PlayerState_Enum_Union & id, const ActionType & type){
	changeState(actor, IState::StateElement(static_cast<int>(id), type));
}

bool PlayerStateMgr_Union::get_state(const PlayerState_Enum_Union & id){
	return currentState(static_cast<int>(id));
}
