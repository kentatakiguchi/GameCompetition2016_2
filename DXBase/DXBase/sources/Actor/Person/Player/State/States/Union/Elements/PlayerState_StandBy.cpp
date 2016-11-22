#include "PlayerState_StandBy.h"

PlayerState_StandBy::PlayerState_StandBy(const PlayerPtr& player) : PlayerState_Union(player) {}

void PlayerState_StandBy::unique_init(){}

void PlayerState_StandBy::update(float deltaTime){
	player_->body_gravity();

	change(StateElement((unsigned int)PlayerState_Enum_Union::IDLE));
}

void PlayerState_StandBy::end(){

}
