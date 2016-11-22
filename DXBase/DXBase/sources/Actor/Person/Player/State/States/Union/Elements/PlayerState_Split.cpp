#include "PlayerState_Split.h"

PlayerState_Split::PlayerState_Split(const PlayerPtr& player) : PlayerState_Union(player) {}

void PlayerState_Split::unique_init(){
	struct_.butty()->reset_enemy();
	struct_.retty()->reset_enemy();

	struct_.butty()->reset_dead_limit();
	struct_.retty()->reset_dead_limit();
}

void PlayerState_Split::update(float deltaTime){
	time_ += deltaTime;

	struct_.butty()->single_action(deltaTime);
	struct_.retty()->single_action(deltaTime);

	struct_.butty()->count_dead_limit(deltaTime);
	struct_.retty()->count_dead_limit(deltaTime);

	if (struct_.butty()->isDead() && struct_.retty()->isDead())change(StateElement((unsigned int)PlayerState_Enum_Union::DEAD));
}

void PlayerState_Split::end(){
	struct_.butty()->init_state();
	struct_.retty()->init_state();
	struct_.butty()->reset_partner();
	struct_.retty()->reset_partner();
}

