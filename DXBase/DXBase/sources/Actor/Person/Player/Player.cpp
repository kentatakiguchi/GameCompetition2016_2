#include "Player.h"

#include"../../Body/CollisionBase.h"

#include "PlayerBody.h"
#include "PlayerConnector.h"

#include "../../../Define.h"
 
#include "../../../Scene/Base/SceneDataKeeper.h"

#include "../../UIActor/HurryUpUI/HurryUpUI.h"

// �R���X�g���N�^
Player::Player(IWorld * world, const Vector2 & position) :
	Actor(world, "Player", position, CollisionBase()),
	prePos_(Vector2::Zero){
	// body�̐���
	create_bodys();
	// �R�l�N�^�̐���
	connect();
	// 
	world_->addUIActor(std::make_shared<HurryUpUI>(world_));
}

// �f�X�g���N�^
Player::~Player() {}

// �X�V����
void Player::onUpdate(float deltaTime) {
	// ���W���̃v���C���[�̒��S�ɌŒ�
	position_ = center();

	world_->GetKeeper()->addMoveDistance(Vector2::Distance(position_, prePos_));

	prePos_ = position_;
	// �w��state�̍X�V
	//if (!world_->GetPlayerNotMove()) {
		update_state(deltaTime);
	//}
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
		if (is_dead()) dead();
	}
	else std::dynamic_pointer_cast<PlayerConnector>(cntr)->onUpdate(deltaTime);// state_update(deltaTime);

	if (position_.y >= CHIPSIZE * 60)dead();
}

// �ڑ�����
void Player::connect() {
	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_PUYON), DX_PLAYTYPE_BACK);
	addChild(std::make_shared<PlayerConnector>(world_, position_, butty_, retty_));
}

// �ڑ��\���ǂ���
bool Player::is_connectable() {
	bool is_main_standby = butty_->stateMgr().currentState((unsigned int)PlayerState_Enum_Single::STAND_BY);
	bool is_sub_standby = retty_->stateMgr().currentState((unsigned int)PlayerState_Enum_Single::STAND_BY);

	return is_main_standby || is_sub_standby;
}

// ���S�������ǂ���
bool Player::is_dead() {
	return butty_->isDead() && retty_->isDead();
}

void Player::setClampPoint(Vector2 point)
{
	butty_->setClampPoint(point);
	retty_->setClampPoint(point);
}
