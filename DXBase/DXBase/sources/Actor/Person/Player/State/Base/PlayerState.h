#pragma once

#include "../Base/IState.h"

#include "../../PlayerBody.h"

#include "../../Player.h"

class PlayerState : public IState {
//public:
//	using PlayerBodyPtr = std::shared_ptr<PlayerBody>;

public:
	PlayerState();

	virtual void common_init(Actor & actor, ActionType type) override;

	virtual void change(StateElement element) override;

	virtual bool isEnd() override;

	virtual StateElement next() const override;
protected:
	Player::PlayerBodyPtr compareMax(Player::PlayerBodyPtr p1, Player::PlayerBodyPtr p2);
	Player::PlayerBodyPtr compareMin(Player::PlayerBodyPtr p1, Player::PlayerBodyPtr p2);
protected:
	StateElement element_;
	bool isEnd_;
	
	Player* player_;
	Player::PlayerBodyPtr main_body_;
	Player::PlayerBodyPtr sub_body_;
};