#include "PlayerStateMgr_Single.h"

#include "StatePath_Single.h"

PlayerStateMgr_Single::PlayerStateMgr_Single(const std::string& name){
	//if (name == "")return;
	
	PlayerState_Single::Keys keys;

	if (name == "PlayerBody1")keys = PlayerState_Single::Keys(KeyCode::UP, KeyCode::DOWN, KeyCode::RIGHT, KeyCode::LEFT);
	if (name == "PlayerBody2")keys = PlayerState_Single::Keys(KeyCode::W, KeyCode::S, KeyCode::D, KeyCode::A);

	add(PlayerState_Enum_Single::STAND_BY, std::make_shared<PlayerState_Single_StandBy>(keys));
	add(PlayerState_Enum_Single::LEAN_BACK, std::make_shared<PlayerState_Single_LeanBack>(keys));
	add(PlayerState_Enum_Single::IDLE, std::make_shared<PlayerState_Single_Idle>(keys));
	add(PlayerState_Enum_Single::MOVE, std::make_shared<PlayerState_Single_Move>(keys));
	add(PlayerState_Enum_Single::DEAD, std::make_shared<PlayerState_Single_Dead>(keys));
}

void PlayerStateMgr_Single::add(const PlayerState_Enum_Single & id, const IStatePtr & state) {
	addState(static_cast<int>(id), state);
}

void PlayerStateMgr_Single::change(Actor & actor, const PlayerState_Enum_Single & id, const ActionType & type){
	changeState(actor, IState::StateElement(static_cast<int>(id), type));
}

bool PlayerStateMgr_Single::get_state(const PlayerState_Enum_Single & id){
	return currentState(static_cast<int>(id));
}

