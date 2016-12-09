#include "PlayerStateMgr_Union.h"

#include "StatePath_Union.h"

PlayerStateMgr_Union::PlayerStateMgr_Union(){
	add(PlayerState_Enum_Union::STAND_BY, std::make_shared<PlayerState_StandBy>());
	add(PlayerState_Enum_Union::IDLE, std::make_shared<PlayerState_Idle>());
	add(PlayerState_Enum_Union::MOVE, std::make_shared<PlayerState_Move>());
	add(PlayerState_Enum_Union::MOVE_BOTH, std::make_shared<PlayerState_MoveBoth>());
	add(PlayerState_Enum_Union::JUMP, std::make_shared<PlayerState_Jump>());
	add(PlayerState_Enum_Union::HOLD, std::make_shared<PlayerState_Hold>());
	add(PlayerState_Enum_Union::HOLD_BOTH, std::make_shared<PlayerState_HoldBoth>());
	add(PlayerState_Enum_Union::ATTACK, std::make_shared<PlayerState_Attack>());
	add(PlayerState_Enum_Union::FREEZE, std::make_shared<PlayerState_Freeze>());
	add(PlayerState_Enum_Union::DEAD, std::make_shared<PlayerState_Dead>());
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