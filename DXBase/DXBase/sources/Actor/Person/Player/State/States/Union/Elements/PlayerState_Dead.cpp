#include "PlayerState_Dead.h"

PlayerState_Dead::PlayerState_Dead(const PlayerPtr& player) : PlayerState_Union(player) {}

void PlayerState_Dead::unique_init(){
}

void PlayerState_Dead::update(float deltaTime){
}

void PlayerState_Dead::end(){
}
