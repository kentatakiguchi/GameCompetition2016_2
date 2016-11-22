#include "PlayerState_Damage.h"

PlayerState_Damage::PlayerState_Damage(const PlayerPtr& player) : PlayerState_Union(player) {}

void PlayerState_Damage::unique_init(){
	//actor.setMotion(6);
}

void PlayerState_Damage::update(float deltaTime){
	//if (actor.getAnim().isAnimEnd()) {
	//	change(StateElement((unsigned int)PlayerState_Enum_Union::IDLE));
	//}
}

void PlayerState_Damage::end(){
}
