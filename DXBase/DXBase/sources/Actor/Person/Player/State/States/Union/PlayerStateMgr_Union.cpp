#include "PlayerStateMgr_Union.h"

#include "StatePath_Union.h"

PlayerStateMgr_Union::PlayerStateMgr_Union(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty){
	add(PlayerState_Enum_Union::STAND_BY, std::make_shared<PlayerState_StandBy>(butty, retty));
	add(PlayerState_Enum_Union::IDLE, std::make_shared<PlayerState_Idle>(butty, retty));
	add(PlayerState_Enum_Union::MOVE_R, std::make_shared<PlayerState_MoveEachR>(butty, retty));
	add(PlayerState_Enum_Union::MOVE_L, std::make_shared<PlayerState_MoveEachL>(butty, retty));
	add(PlayerState_Enum_Union::MOVE_BOTH, std::make_shared<PlayerState_MoveBoth>(butty, retty));
	add(PlayerState_Enum_Union::JUMP, std::make_shared<PlayerState_Jump>(butty, retty));
	add(PlayerState_Enum_Union::HOLD, std::make_shared<PlayerState_HoldInit>(butty, retty));
	add(PlayerState_Enum_Union::HOLD_BEGIN, std::make_shared<PlayerState_HoldBegin>(butty, retty));
	add(PlayerState_Enum_Union::HOLD_SWIM, std::make_shared<PlayerState_HoldSwim>(butty, retty));
	add(PlayerState_Enum_Union::HOLD_FULL, std::make_shared<PlayerState_HoldFull>(butty, retty));
	add(PlayerState_Enum_Union::HOLD_AIR, std::make_shared<PlayerState_HoldAirBegin>(butty, retty));
	add(PlayerState_Enum_Union::HOLD_AIR_SWIM, std::make_shared<PlayerState_HoldAirSwim>(butty, retty));
	add(PlayerState_Enum_Union::HOLD_AIR_FULL, std::make_shared<PlayerState_HoldAirFull>(butty, retty));
	add(PlayerState_Enum_Union::HOLD_BOTH, std::make_shared<PlayerState_HoldBoth>(butty, retty));
	add(PlayerState_Enum_Union::HOLD_ITEM, std::make_shared<PlayerState_HoldItem>(butty, retty));
	add(PlayerState_Enum_Union::ATTACK_R, std::make_shared<PlayerState_AttackR>(butty, retty));
	add(PlayerState_Enum_Union::ATTACK_L, std::make_shared<PlayerState_AttackL>(butty, retty));
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
