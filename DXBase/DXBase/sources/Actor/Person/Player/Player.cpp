#include "Player.h"

#include"../../Body/CollisionBase.h"
#include "../../../ResourceLoader/ResourceLoader.h"

#include "State/States/Union/StatePath_Union.h"

#include "PlayerConnector.h"

#include "../../../Game/Time.h"
#include <memory>
#include <algorithm>
#include "../../TestPlayer/TestPlayer.h"

Player::Player(IWorld * world, const Vector2 & position) :
	Actor(world, "Player", position, CollisionBase(Vector2(0, 0), Vector2(0, 0), 8.0f))
{

	auto body1 = std::make_shared<PlayerBody>(world_, "PlayerBody1", position_ + Vector2::Right * PLAYER_MAX_NORMAL_LENGTH / 2);
	auto body2 = std::make_shared<PlayerBody>(world_, "PlayerBody2", position_ - Vector2::Right * PLAYER_MAX_NORMAL_LENGTH / 2);

	addChild(body1);
	addChild(body2);

	butty_ = body1;
	retty_ = body2;

	set_body();

	connect();
}

Player::~Player() {
}

void Player::onUpdate(float deltaTime) {
	position_ = (butty_->getPosition() + retty_->getPosition()) / 2;

	auto cntr = findCildren(std::string("PlayerConnector"));
	if (cntr == nullptr) {
		butty_->single_action(deltaTime);
		retty_->single_action(deltaTime);
		if (is_connectable()) connect();
	}
	else {
		auto tmp = std::dynamic_pointer_cast<PlayerConnector>(cntr);
		if (tmp->state_mgr().get_state(PlayerState_Enum_Union::DEAD)) dead();
		tmp->state_action(deltaTime);
	}
}

void Player::onLateUpdate(float deltaTime) {
}

void Player::onDraw() const {
	//DrawFormatString(25, 25, GetColor(255, 255, 255), "%d", stateMgr_.currentState());
}

void Player::onCollide(Actor & other) {}

PlayerBodyPtr Player::blue_body() {
	return butty_;
}

PlayerBodyPtr Player::red_body() {
	return retty_;
}

PlayerCntrPtr Player::connector() {
	//auto tmp = findCildren(std::string("PlayerConnector"));
	return  nullptr;
}

void Player::set_body() {
	butty_->set_partner(retty_);
	retty_->set_partner(butty_);
}

void Player::connect() {
	auto cntr = std::make_shared<PlayerConnector>(world_, position_, butty_, retty_);
	addChild(cntr);
	//cntr_ = cntr;
}

bool Player::is_connectable() {
	bool is_main_target_partner = butty_->hit_partner() == HitOpponent::PARTNER;
	bool is_sub_target_partner = retty_->hit_partner() == HitOpponent::PARTNER;
	bool for_debug = InputMgr::GetInstance().IsKeyDown(KeyCode::C);

	return (is_main_target_partner || is_sub_target_partner || for_debug);
}

bool Player::is_dead() {
	bool is_main_dead = butty_->dead_limit();
	bool is_main_target_enemy = butty_->hit_enemy() == HitOpponent::ENEMY;
	bool is_main_invincible = butty_->isInv();

	bool is_sub_dead = retty_->dead_limit();
	bool is_sub_target_enemy = retty_->hit_enemy() == HitOpponent::ENEMY;
	bool is_sub_invincible = retty_->isInv();

	return (is_main_dead && is_sub_dead) || (is_main_target_enemy && !is_main_invincible) || (is_sub_target_enemy && !is_sub_invincible);
}






