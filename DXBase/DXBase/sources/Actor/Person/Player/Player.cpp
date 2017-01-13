#include "Player.h"

#include"../../Body/CollisionBase.h"

#include "PlayerBody.h"
#include "PlayerConnector.h"

// コンストラクタ
Player::Player(IWorld * world, const Vector2 & position) :
	Actor(world, "Player", position, CollisionBase()) {
	// bodyの生成
	create_bodys();
	// コネクタの生成
	connect();
}

// デストラクタ
Player::~Player() {}

// 更新処理
void Player::onUpdate(float deltaTime) {
	// 座標を中心に固定
	position_ = center();

	// 指定stateの更新
	if (!world_->GetPlayerNotMove()) update_state(deltaTime);
}

// body中心座標
Vector2 Player::center() {
	return (butty_->getPosition() + retty_->getPosition()) / 2;
}

// body生成
void Player::create_bodys() {
	auto body1 = std::make_shared<PlayerBody>(world_, "PlayerBody1", position_ + Vector2::Right * PLAYER_MAX_NORMAL_LENGTH / 2);
	auto body2 = std::make_shared<PlayerBody>(world_, "PlayerBody2", position_ - Vector2::Right * PLAYER_MAX_NORMAL_LENGTH / 2);

	addChild(body1);
	addChild(body2);

	butty_ = body1;
	retty_ = body2;

	butty_->set_partner(retty_);
	retty_->set_partner(butty_);
}

// 指定stateの更新処理
void Player::update_state(float deltaTime) {
	auto cntr = findCildren(std::string("PlayerConnector"));
	if (cntr == nullptr) {
		butty_->single_action(deltaTime);
		retty_->single_action(deltaTime);
		if (is_connectable()) connect();
		if (is_dead()) {
			butty_->change_state(PlayerState_Enum_Single::DEAD);
			retty_->change_state(PlayerState_Enum_Single::DEAD);
			if (butty_->isDead() && retty_->isDead()) dead();
		}
	}
	else std::dynamic_pointer_cast<PlayerConnector>(cntr)->state_update(deltaTime);

	if (position_.y >= 96 * 60)dead();
}

// 接続処理
void Player::connect() {
	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_PUYON), DX_PLAYTYPE_BACK);
	addChild(std::make_shared<PlayerConnector>(world_, position_, butty_, retty_));
}

// 接続可能かどうか
bool Player::is_connectable() {
	bool is_main_target_partner = butty_->hit_partner() == HitOpponent::PARTNER;
	bool is_sub_target_partner = retty_->hit_partner() == HitOpponent::PARTNER;
	bool for_debug = false;	//InputMgr::GetInstance().IsKeyDown(KeyCode::C);

	return (is_main_target_partner || is_sub_target_partner || for_debug);
}

// 死亡したかどうか
bool Player::is_dead() {
	bool is_main_dead = butty_->dead_limit();
	bool is_main_target_enemy = butty_->hit_enemy() == HitOpponent::ENEMY;
	bool is_main_invincible = butty_->isInv();

	bool is_sub_dead = retty_->dead_limit();
	bool is_sub_target_enemy = retty_->hit_enemy() == HitOpponent::ENEMY;
	bool is_sub_invincible = retty_->isInv();

	return (is_main_dead && is_sub_dead) || (is_main_target_enemy && !is_main_invincible) || (is_sub_target_enemy && !is_sub_invincible);
}






