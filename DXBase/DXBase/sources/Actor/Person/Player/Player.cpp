#include "Player.h"

#include"../../Body/CollisionBase.h"
#include "../../../ResourceLoader/ResourceLoader.h"

#include "State/Base/State_Dammy.h"
#include "State/States/Union/Elements/PlayerState_StandBy.h"
#include "State/States/Union/Elements/PlayerState_Idle.h"
#include "State/States/Union/Elements/PlayerState_Move.h"
#include "State/States/Union/Elements/PlayerState_Hold.h"
#include "State/States/Union/Elements/PlayerState_HoldBoth.h"
#include "State/States/Union/Elements/PlayerState_Attack.h"
#include "State/States/Union/Elements/PlayerState_Damage.h"
#include "State/States/Union/Elements/PlayerState_Split.h"

#include "../../../Renderer/DrawShape.h"

#include <memory>
#include <algorithm>

Player::Player(IWorld * world, const Vector2 & position) :
	Actor(world, "Player", position, CollisionBase(Vector2(0, 0), Vector2(0, 0), 8.0f)){
	// モデルの読み込み
	//modelHandle_ = MV1DuplicateModel(ResourceLoader::GetInstance().getModelID(ModelID::PLAYER));
	//animation_ = Animation(modelHandle_);
	
	auto body1 = std::make_shared<PlayerBody>(world_, "PlayerBody1", position_ + Vector2(PLAYER_MAX_NORMAL_LENGTH / 2, 0));
	auto body2 = std::make_shared<PlayerBody>(world_, "PlayerBody2", position_ - Vector2(PLAYER_MAX_NORMAL_LENGTH / 2, 0));
	auto cntr = std::make_shared<PlayerConnector>(world_, body1, body2);

	addChild(body1);
	addChild(body2);
	addChild(cntr);

	stateMgr_.add((unsigned int)PlayerState_Enum_Union::STAND_BY, std::make_shared<PlayerState_StandBy>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::IDLE, std::make_shared<PlayerState_Idle>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::MOVE, std::make_shared<PlayerState_Move>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::HOLD, std::make_shared<PlayerState_Hold>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::HOLD_BOTH, std::make_shared<PlayerState_HoldBoth>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::QUICK, std::make_shared<PlayerState_Move>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::ATTACK, std::make_shared<PlayerState_Attack>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::DAMAGE, std::make_shared<PlayerState_Damage>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::SPLIT, std::make_shared<PlayerState_Split>());
	stateMgr_.changeState(*this, IState::StateElement((unsigned int)PlayerState_Enum_Union::STAND_BY));

	//world_->addActor(ActorGroup::Player, std::make_shared<PlayerBody_Connector>(world_, position_));
	//connector_ = std::static_pointer_cast<PlayerConnector>(findCildren((const std::string)"PlayerConnector"));
}

Player::~Player(){}

void Player::onUpdate(float deltaTime) {

	stateMgr_.action(*this, deltaTime);

	Vector2 main_pos = Vector2(main_->getPosition().x, main_->getPosition().y);
	Vector2 sub_pos = Vector2(sub_->getPosition().x, sub_->getPosition().y);
	position_ = (main_pos + sub_pos) / 2;
	body_.RotateCapsule(main_pos - position_, sub_pos - position_, body_.GetCapsule().component_.radius);

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::P) && stateMgr_.currentState() != (unsigned int)PlayerState_Enum_Union::SPLIT) {
		stateMgr_.changeState(*this, IState::StateElement((unsigned int)PlayerState_Enum_Union::SPLIT));
	}
	// 新しい座標を保存する
	//position_ = Vector3::Lerp(position_, curPosition, 0.8f);

	DrawFormatString(25, 25, GetColor(255, 255, 255), "%d", stateMgr_.currentState());
}

void Player::onLateUpdate(float deltaTime){
}

void Player::onDraw() const {
	//connector_->set_point(main_body_, sub_body_);

	//body_.draw(/*inv()*/);
	DrawShape::Oval(main_->getPosition(), sub_->getPosition(), body_.GetCapsule().component_.radius * 5, PLAYER_MAX_NORMAL_LENGTH);

 	DrawFormatString(static_cast<int>(main_->getPosition().x), static_cast<int>(main_->getPosition().y), GetColor(255, 255, 255), "main");
	DrawFormatString(static_cast<int>(sub_->getPosition().x), static_cast<int>(sub_->getPosition().y), GetColor(255, 255, 255), "sub");
}

void Player::onCollide(Actor & other){
	//if (stateMgr_.currentState() == (unsigned int)Player_EnumState::DAMAGE)return;
}

void Player::changeMotion(float deltaTime){

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::L)) {
		motion_ = (motion_ + 1) % 10;
		//animation_.changeAnim(motion_);
	}
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::K)) {
		motion_ = ((motion_ - 1) + 10) % 10;
		//animation_.changeAnim(motion_);
	}
}

void Player::setBody(PlayerBodyPtr main, PlayerBodyPtr sub){
	main_ = main;	
	sub_ = sub;
}

PlayerBodyPtr Player::getMainBody() {
	return main_;
}
PlayerBodyPtr Player::getSubBody(){
	return sub_;
}

void Player::createWindow()
{
	int handle, i, j, grhandle;

	// 空のフルカラー画像を作成する
	handle = MakeARGB8ColorSoftImage(256, 256);

	// 縦方向に透明グラデーションした真っ赤な画像を作成する
	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < 256; j++)
		{
			// 色をセット
			DrawPixelSoftImage(handle, j, i, 255, 0, 0, i);
		}
	}

	// 透明かどうかわかるように画面を緑で塗りつぶす
	DrawBox(0, 0, 640, 480, GetColor(0, 255, 0), TRUE);

	// グラフィックハンドルを作成
	grhandle = CreateGraphFromSoftImage(handle);

	// 使い終わったら解放
	DeleteSoftImage(handle);

	// グラフィックハンドルを描画
	DrawGraph(0, 0, grhandle, TRUE);
}


