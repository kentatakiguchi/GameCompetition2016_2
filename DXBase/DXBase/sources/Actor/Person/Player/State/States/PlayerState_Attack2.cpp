#include "PlayerState_Attack2.h"
#include "../Player_EnumState.h"

#include "../../Player_AttackRange.h"

PlayerState_Attack2::PlayerState_Attack2(){}

void PlayerState_Attack2::unique_init(Actor & actor) {
	actor.getWorld()->addActor(ActorGroup::Player_AttackRange, std::make_shared<Player_AttackRange>(actor.getWorld(), actor.getPosition()));
	actor.setMotion(1);
}

void PlayerState_Attack2::update(Actor & actor, float deltaTime) {
	if (actor.getAnim().isAnimEnd()) {
		change((unsigned int)Player_EnumState::IDLE);
	}
}

void PlayerState_Attack2::end() {

}



