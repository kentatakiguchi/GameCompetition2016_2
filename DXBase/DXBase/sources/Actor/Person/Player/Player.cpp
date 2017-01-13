#include "Player.h"

#include"../../Body/CollisionBase.h"

#include "PlayerBody.h"
#include "PlayerConnector.h"

// �R���X�g���N�^
Player::Player(IWorld * world, const Vector2 & position) :
	Actor(world, "Player", position, CollisionBase()) {
	// body�̐���
	create_bodys();
	// �R�l�N�^�̐���
	connect();
}

// �f�X�g���N�^
Player::~Player() {}

// �X�V����
void Player::onUpdate(float deltaTime) {
	// ���W�𒆐S�ɌŒ�
	position_ = center();

	// �w��state�̍X�V
	if (!world_->GetPlayerNotMove()) update_state(deltaTime);
}

// body���S���W
Vector2 Player::center() {
	return (butty_->getPosition() + retty_->getPosition()) / 2;
}

// body����
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

// �w��state�̍X�V����
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

// �ڑ�����
void Player::connect() {
	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_PUYON), DX_PLAYTYPE_BACK);
	addChild(std::make_shared<PlayerConnector>(world_, position_, butty_, retty_));
}

// �ڑ��\���ǂ���
bool Player::is_connectable() {
	bool is_main_target_partner = butty_->hit_partner() == HitOpponent::PARTNER;
	bool is_sub_target_partner = retty_->hit_partner() == HitOpponent::PARTNER;
	bool for_debug = false;	//InputMgr::GetInstance().IsKeyDown(KeyCode::C);

	return (is_main_target_partner || is_sub_target_partner || for_debug);
}

// ���S�������ǂ���
bool Player::is_dead() {
	bool is_main_dead = butty_->dead_limit();
	bool is_main_target_enemy = butty_->hit_enemy() == HitOpponent::ENEMY;
	bool is_main_invincible = butty_->isInv();

	bool is_sub_dead = retty_->dead_limit();
	bool is_sub_target_enemy = retty_->hit_enemy() == HitOpponent::ENEMY;
	bool is_sub_invincible = retty_->isInv();

	return (is_main_dead && is_sub_dead) || (is_main_target_enemy && !is_main_invincible) || (is_sub_target_enemy && !is_sub_invincible);
}






