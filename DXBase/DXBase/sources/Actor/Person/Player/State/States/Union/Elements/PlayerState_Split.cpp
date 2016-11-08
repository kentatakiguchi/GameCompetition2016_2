#include "PlayerState_Split.h"

PlayerState_Split::PlayerState_Split()
{
}

void PlayerState_Split::unique_init(Actor & actor)
{
}

void PlayerState_Split::update(Actor & actor, float deltaTime){
	main_body_->single_action(deltaTime);
	sub_body_->single_action(deltaTime);

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::O)) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::IDLE));
	}
}

void PlayerState_Split::end()
{
}

void PlayerState_Split::move(Actor & actor, float deltaTime)
{
}
